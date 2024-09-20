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

	void WindowEx::MinWidth(int32_t const& Value)
	{
		m_MinWidth = Value;
	}

	int32_t WindowEx::MinHeight()
	{
		return m_MinHeight;
	}

	void WindowEx::MinHeight(int32_t const& Value)
	{
		m_MinHeight = Value;
	}
	
	bool WindowEx::IsMinimizable()
	{ 
		return m_Presenter.IsMinimizable();
	}
	
	void WindowEx::IsMinimizable(bool const& Value)
	{
		m_Presenter.IsMinimizable(Value);
	}

	bool WindowEx::IsMaximizable()
	{
		return m_Presenter.IsMaximizable();
	}

	void WindowEx::IsMaximizable(bool const& Value)
	{
		m_Presenter.IsMaximizable(Value);
	}

	bool WindowEx::IsResizable()
	{
		return m_Presenter.IsResizable();
	}

	void WindowEx::IsResizable(bool const& Value)
	{
		m_Presenter.IsResizable(Value);
	}

	bool WindowEx::IsAlwaysOnTop()
	{
		return m_Presenter.IsAlwaysOnTop();
	}

	void WindowEx::IsAlwaysOnTop(bool const& Value)
	{
		m_Presenter.IsAlwaysOnTop(Value);
	}

	bool WindowEx::ExtendsClientArea()
	{
		return m_ExtendsClientArea;
	}

	void WindowEx::ExtendsClientArea(bool const& Value)
	{
		MARGINS Margins{ 0, 0, 0, 0 };
		
		m_ExtendsClientArea = Value;
		ExtendsContentIntoTitleBar(Value);

		if (m_ExtendsClientArea)
		{
			Margins.cyTopHeight = 2;
		}

		::DwmExtendFrameIntoClientArea(m_hWnd, &Margins);

		/* Force a WM_NCCALCSIZE message, which specifies the client area size */
		//::SetWindowPos(m_hWnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
	}

	float WindowEx::DpiScale()
	{
		return m_DpiScale;
	}
}