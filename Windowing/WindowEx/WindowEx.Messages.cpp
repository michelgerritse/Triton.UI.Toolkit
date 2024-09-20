/*
 _____    _ _             _   _ ___ _____         _ _   _ _
|_   _| _(_) |_ ___ _ _  | | | |_ _|_   _|__  ___| | |_(_) |_
  | || '_| |  _/ _ \ ' \ | |_| || | _| |/ _ \/ _ \ | / / |  _|
  |_||_| |_|\__\___/_||_(_)___/|___(_)_|\___/\___/_|_\_\_|\__|

Copyright © 2024, Michel Gerritse
All rights reserved.

This source code is available under the BSD-3-Clause license.
See LICENSE.txt in the root directory of this source tree.

*/
#include "pch.h"
#include "WindowEx.h"

namespace winrt::Triton::UI::Windowing::implementation
{
	LRESULT WindowEx::OnDestroy()
	{
		/* Reference: https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-destroy */
		
		auto WndProc = m_OriginalWndProc;

		if (m_hWndChild) RestoreWindowSubclass(m_hWndChild, m_OriginalChildWndProc);
		RestoreWindowSubclass(m_hWnd, m_OriginalWndProc);

		return ::CallWindowProc(WndProc, m_hWnd, WM_DESTROY, 0, 0);
	}

	LRESULT WindowEx::OnDpiChanged(WPARAM wParam, LPARAM lParam)
	{
		/* Reference: https://learn.microsoft.com/en-us/windows/win32/hidpi/wm-dpichanged */

		m_Dpi = HIWORD(wParam);
		m_DpiScale = (float)m_Dpi / 96.f;

		return ::CallWindowProc(m_OriginalWndProc, m_hWnd, WM_DPICHANGED, wParam, lParam);
	}

	LRESULT WindowEx::OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo)
	{
		/* Reference: https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-getminmaxinfo */
		
		lpMinMaxInfo->ptMinTrackSize.x = ::MulDiv(m_MinWidth,  m_Dpi, USER_DEFAULT_SCREEN_DPI);
		lpMinMaxInfo->ptMinTrackSize.y = ::MulDiv(m_MinHeight, m_Dpi, USER_DEFAULT_SCREEN_DPI);

		return 0;
	}

	LRESULT WindowEx::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
	{
		/* Reference: https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-nccalcsize */

		if ((wParam == TRUE) && m_ExtendsClientArea)
		{
			NCCALCSIZE_PARAMS* pncsp = (NCCALCSIZE_PARAMS*) lParam;

			auto CxFrame = ::GetSystemMetricsForDpi(SM_CXFRAME, m_Dpi);
			auto CyFrame = ::GetSystemMetricsForDpi(SM_CYFRAME, m_Dpi);
			auto Padding = ::GetSystemMetricsForDpi(SM_CXPADDEDBORDER, m_Dpi);
			//auto Caption = ::GetSystemMetricsForDpi(SM_CYCAPTION, m_Dpi);

			pncsp->rgrc[0].left	  += (CxFrame + Padding);
			pncsp->rgrc[0].right  -= (CxFrame + Padding);
			pncsp->rgrc[0].bottom -= (CyFrame + Padding);

			/* Note: Keep rgrc[0].top untouched to extend the client area into the caption bar */

			return 0;
		}

		return ::CallWindowProc(m_OriginalWndProc, m_hWnd, WM_NCCALCSIZE, wParam, lParam);
	}

	LRESULT WindowEx::OnParentNotify(WPARAM wParam, LPARAM lParam)
	{
		/* Reference: https://learn.microsoft.com/en-us/windows/win32/inputmsg/wm-parentnotify */

		switch (LOWORD(wParam))
		{
		case WM_CREATE:
			if (m_hWndChild == nullptr)
			{
				HWND	Window = (HWND)lParam;
				TCHAR	Buffer[MAX_PATH];
				auto	CharCount = ::GetClassName(Window, Buffer, MAX_PATH);
				hstring	WindowClassName(Buffer, CharCount);

				if (WindowClassName == L"ReunionWindowingCaptionControls")
				{
					m_hWndChild = Window;
					winrt::check_pointer(m_OriginalChildWndProc = InstallWindowSubclass(m_hWndChild, WindowEx::SubclassChildWndProc));
				}
			}
			
			break;
		
		case WM_DESTROY:
			if (m_hWndChild == (HWND)lParam)
			{				
				/*
				Note: it appears this never gets send when the ReunionWindowingCaptionControls window is getting destroyed
				As a precaution the child subclass will also get removed by the parent's WM_DESTROY handler
				*/
				
				RestoreWindowSubclass(m_hWndChild, m_OriginalChildWndProc);
				m_hWndChild = nullptr;
			}
			break;
		}
		
		return ::CallWindowProc(m_OriginalWndProc, m_hWnd, WM_PARENTNOTIFY, wParam, lParam);
	}

	LRESULT WindowEx::OnChildWindowPosChanging(LPWINDOWPOS lpWindowPos)
	{
		/*
		Note: This is a fix for the following problem:
		https://github.com/microsoft/microsoft-ui-xaml/issues/9934

		This has only be tested in Windows 10
		*/
		lpWindowPos->y += 1;

		
		return 0;
	}

	LRESULT CALLBACK WindowEx::SubclassWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		/* Get WindowEx object pointer from window property */
		WindowEx* pThis = (WindowEx*) ::GetProp(hWnd, (LPCWSTR) s_PropertyAtom);
		winrt::check_pointer(pThis);

		/* Handle messages */
		switch (message)
		{
		case WM_DESTROY:		return pThis->OnDestroy();
		case WM_DPICHANGED:		return pThis->OnDpiChanged(wParam, lParam);
		case WM_GETMINMAXINFO:	return pThis->OnGetMinMaxInfo((LPMINMAXINFO) lParam);
		//case WM_NCCALCSIZE:		return pThis->OnNcCalcSize(wParam, lParam);
		case WM_PARENTNOTIFY:	return pThis->OnParentNotify(wParam, lParam);
		}

		return ::CallWindowProc(pThis->m_OriginalWndProc, hWnd, message, wParam, lParam);
	}

	LRESULT WindowEx::SubclassChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		/* Get WindowEx object pointer from window property */
		WindowEx* pThis = (WindowEx*) ::GetProp(hWnd, (LPCWSTR) s_PropertyAtom);
		winrt::check_pointer(pThis);

		/* Handle messages */
		switch (message)
		{
		case WM_WINDOWPOSCHANGING: return pThis->OnChildWindowPosChanging((LPWINDOWPOS) lParam);
		}

		return ::CallWindowProc(pThis->m_OriginalChildWndProc, hWnd, message, wParam, lParam);
	}
}