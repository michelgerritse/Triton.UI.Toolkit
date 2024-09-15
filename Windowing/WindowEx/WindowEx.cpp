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
#include "Windowing.WindowEx.g.cpp"

namespace winrt::Triton::UI::Windowing::implementation
{	
	/* Static class member definition */
	ATOM WindowEx::s_PropertyAtom = 0;

	WindowEx::WindowEx()
	{
		/* Get native window handle */
		auto WindowNative = m_inner.as<::IWindowNative>();
		winrt::check_hresult(WindowNative->get_WindowHandle(&m_hWnd));

		/* Get window DPI */
		m_Dpi = GetDpiForWindow(m_hWnd);

		/* Get presenter */
		m_Presenter = AppWindow().Presenter().as<OverlappedPresenter>();

		/* Register event handler(s) */
		m_AppWindowChangedToken = AppWindow().Changed({ get_weak(), &WindowEx::AppWindowChangedEvent });

		/* Subclass window */
		winrt::check_pointer(m_OriginalWndProc = InstallWindowSubclass(m_hWnd, WindowEx::SubclassWndProc));
	}

	WNDPROC WindowEx::InstallWindowSubclass(HWND hWnd, WNDPROC lpNewWndProc)
	{
		winrt::check_pointer(hWnd);
		winrt::check_pointer(lpNewWndProc);
				
		/* Register property string atom */
		s_PropertyAtom = ::GlobalAddAtom(GetRuntimeClassName().c_str());

		/* Store WindowEx object pointer in window property */
		winrt::check_bool(::SetProp(hWnd, (LPCWSTR)s_PropertyAtom, (HANDLE)this));

		/* Install new window procedure, return original procedure */
		return (WNDPROC) ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)lpNewWndProc);
	}

	void WindowEx::RestoreWindowSubclass(HWND hWnd, WNDPROC lpOriginalWndProc)
	{
		winrt::check_pointer(hWnd);
		winrt::check_pointer(lpOriginalWndProc);

		/* Restore original window procedure */
		::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)lpOriginalWndProc);

		/* Remove window property */
		::RemoveProp(hWnd, (LPCWSTR)s_PropertyAtom);

		/* Unregister property string atom */
		::GlobalDeleteAtom(s_PropertyAtom);
	}
}