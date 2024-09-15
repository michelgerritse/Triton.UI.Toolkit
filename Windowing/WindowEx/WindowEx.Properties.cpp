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
	int32_t WindowEx::MinWidth()
	{
		return m_MinWidth;
	}

	void WindowEx::MinWidth(const int32_t& value)
	{
		m_MinWidth = value;
	}

	int32_t WindowEx::MinHeight()
	{
		return m_MinHeight;
	}

	void WindowEx::MinHeight(const int32_t& value)
	{
		m_MinHeight = value;
	}
	
	bool WindowEx::IsMinimizable()
	{ 
		return m_Presenter.IsMinimizable();
	}
	
	void WindowEx::IsMinimizable(const bool& value)
	{
		m_Presenter.IsMinimizable(value);
	}

	bool WindowEx::IsMaximizable()
	{
		return m_Presenter.IsMaximizable();
	}

	void WindowEx::IsMaximizable(const bool& value)
	{
		m_Presenter.IsMaximizable(value);
	}

	bool WindowEx::IsResizable()
	{
		return m_Presenter.IsResizable();
	}

	void WindowEx::IsResizable(const bool& value)
	{
		m_Presenter.IsResizable(value);
	}

	bool WindowEx::IsAlwaysOnTop()
	{
		return m_Presenter.IsAlwaysOnTop();
	}

	void WindowEx::IsAlwaysOnTop(const bool& value)
	{
		m_Presenter.IsAlwaysOnTop(value);
	}

	bool WindowEx::ExtendsClientArea()
	{
		return m_ExtendsClientArea;
	}

	void WindowEx::ExtendsClientArea(const bool& value)
	{
		MARGINS Margins{ 0, 0, 0, 0 };
		
		m_ExtendsClientArea = value;
		ExtendsContentIntoTitleBar(value);

		if (m_ExtendsClientArea)
		{
			Margins.cyTopHeight = 2;
		}

		::DwmExtendFrameIntoClientArea(m_hWnd, &Margins);

		/* Force a WM_NCCALCSIZE message, which specifies the client area size */
		//::SetWindowPos(m_hWnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
	}
}