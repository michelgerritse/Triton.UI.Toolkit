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
#include "Windowing.WindowEx.g.h"
#include <dwmapi.h>
#include <uxtheme.h>

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "UxTheme.lib")

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Windowing;

namespace winrt::Triton::UI::Windowing::implementation
{
	struct WindowEx : WindowExT<WindowEx>
	{
		WindowEx();

		int32_t		MinWidth();
		void		MinWidth(const int32_t& value);

		int32_t		MinHeight();
		void		MinHeight(const int32_t& value);

		bool		IsMinimizable();
		void		IsMinimizable(const bool& value);
		
		bool		IsMaximizable();
		void		IsMaximizable(const bool& value);
		
		bool		IsResizable();
		void		IsResizable(const bool& value);

		bool		IsAlwaysOnTop();
		void		IsAlwaysOnTop(const bool& value);

		bool		ExtendsClientArea();
		void		ExtendsClientArea(const bool& value);

		void		AppWindowChangedEvent(IInspectable const& sender, AppWindowChangedEventArgs const& e);

	private:
		HWND		m_hWnd{ nullptr };
		HWND		m_hWndChild{ nullptr };
		WNDPROC		m_OriginalWndProc{ nullptr };
		WNDPROC		m_OriginalChildWndProc{ nullptr };
		uint32_t	m_Dpi{ USER_DEFAULT_SCREEN_DPI };
		int32_t		m_MinWidth{ 0 };
		int32_t		m_MinHeight{ 0 };
		bool		m_ExtendsClientArea{ false };

		OverlappedPresenter m_Presenter{ nullptr };
		event_token			m_AppWindowChangedToken;

		WNDPROC		InstallWindowSubclass(HWND hWnd, WNDPROC lpNewWndProc);
		void		RestoreWindowSubclass(HWND hWnd, WNDPROC lpOriginalWndProc);

		LRESULT		OnDestroy();
		LRESULT		OnDpiChanged(WPARAM wParam, LPARAM lParam);
		LRESULT		OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo);
		LRESULT		OnNcCalcSize(WPARAM wParam, LPARAM lParam);
		LRESULT		OnParentNotify(WPARAM wParam, LPARAM lParam);

		LRESULT		OnChildWindowPosChanging(LPWINDOWPOS lpWindowPos);

		static ATOM s_PropertyAtom;

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