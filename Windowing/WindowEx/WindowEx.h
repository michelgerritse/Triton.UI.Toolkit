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
#pragma once
#include "pch.h"
#include "Windowing/WindowEx.g.h"
#include <dwmapi.h>
#include <uxtheme.h>

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "UxTheme.lib")

using namespace winrt;
using namespace Microsoft::UI::Input;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Windowing;

namespace winrt::Triton::UI::Windowing::implementation
{
	struct WindowEx : WindowExT<WindowEx>
	{
		WindowEx();

		/* Properties (read/write) */
		int32_t		MinWidth();
		void		MinWidth(int32_t const&);

		int32_t		MinHeight();
		void		MinHeight(int32_t const&);

		bool		IsMinimizable();
		void		IsMinimizable(bool const&);
		
		bool		IsMaximizable();
		void		IsMaximizable(bool const&);
		
		bool		IsResizable();
		void		IsResizable(bool const&);

		bool		IsAlwaysOnTop();
		void		IsAlwaysOnTop(bool const&);

		bool		ExtendsClientArea();
		void		ExtendsClientArea(bool const&);

		/* Properties (read only) */
		float		DpiScale();

	private:
		HWND		m_hWnd{ nullptr };
		HWND		m_hWndChild{ nullptr };
		
		WNDPROC		m_OriginalWndProc{ nullptr };
		WNDPROC		m_OriginalChildWndProc{ nullptr };
		
		uint32_t	m_Dpi{ USER_DEFAULT_SCREEN_DPI };
		float		m_DpiScale{ 1.0 };
		
		int32_t		m_MinWidth{ 0 };
		int32_t		m_MinHeight{ 0 };
		
		bool		m_ExtendsClientArea{ false };

		OverlappedPresenter m_Presenter{ nullptr };
		Microsoft::UI::WindowId m_WindowId{ 0 };

		static ATOM s_PropertyAtom;

		/* Win32 subclassing */
		WNDPROC	InstallWindowSubclass(HWND hWnd, WNDPROC lpNewWndProc);
		void	RestoreWindowSubclass(HWND hWnd, WNDPROC lpOriginalWndProc);

		/* Win32 window messages */
		LRESULT	OnDestroy();
		LRESULT	OnDpiChanged(WPARAM wParam, LPARAM lParam);
		LRESULT	OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo);
		LRESULT	OnNcCalcSize(WPARAM wParam, LPARAM lParam);
		LRESULT	OnParentNotify(WPARAM wParam, LPARAM lParam);

		/* Win32 child window messages */
		LRESULT	OnChildWindowPosChanging(LPWINDOWPOS lpWindowPos);

		/* Win32 window procedures */
		static LRESULT CALLBACK SubclassWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK SubclassChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}

namespace winrt::Triton::UI::Windowing::factory_implementation
{
	struct WindowEx : WindowExT<WindowEx, implementation::WindowEx>
	{
	};
}