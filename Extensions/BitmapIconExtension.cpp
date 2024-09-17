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
#include "BitmapIconExtension.h"
#include "Extensions.BitmapIconExtension.g.cpp"

/* References:
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.markup.markupextension
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.controls.bitmapicon
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.controls.iconelement
*/

namespace winrt::Triton::UI::Extensions::implementation
{
/* MarkupExtension overrides */
#pragma region MarkupExtension overrides

	IInspectable BitmapIconExtension::ProvideValue()
	{
		BitmapIcon Icon;

		Icon.ShowAsMonochrome(m_ShowAsMonochrome);
		Icon.UriSource(m_UriSource);
		if (m_Foreground) Icon.Foreground(m_Foreground);
		
		return Icon;
	}

	IInspectable BitmapIconExtension::ProvideValue(IXamlServiceProvider const&)
	{
		return ProvideValue();
	}

#pragma endregion
	
/* BitmapIcon properties */
#pragma region BitmapIcon properties

	bool BitmapIconExtension::ShowAsMonochrome()
	{
		return m_ShowAsMonochrome;
	}

	void BitmapIconExtension::ShowAsMonochrome(bool Value)
	{
		m_ShowAsMonochrome = Value;
	}

	wf::Uri BitmapIconExtension::UriSource()
	{
		return m_UriSource;
	}

	void BitmapIconExtension::UriSource(wf::Uri Value)
	{
		m_UriSource = Value;
	}

#pragma endregion
	
/* BitmapIcon properties inherited from IconElement */
#pragma region BitmapIcon properties inherited from IconElement

	muxm::Brush BitmapIconExtension::Foreground()
	{
		return m_Foreground;
	}
	
	void BitmapIconExtension::Foreground(muxm::Brush Value)
	{
		m_Foreground = Value;
	}

#pragma endregion
}