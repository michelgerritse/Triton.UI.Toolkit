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
#include "FontIconExtension.h"
#include "Extensions.FontIconExtension.g.cpp"

/* References:
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.markup.markupextension
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.controls.fonticon
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.controls.iconelement
*/

namespace winrt::Triton::UI::Extensions::implementation
{
/* MarkupExtension overrides */
#pragma region MarkupExtension overrides

	IInspectable FontIconExtension::ProvideValue()
	{
		FontIcon Icon;

		if (m_FontFamily) Icon.FontFamily(m_FontFamily);
		Icon.FontSize(m_FontSize);
		Icon.FontStyle(m_FontStyle);
		Icon.FontWeight(m_FontWeight);
		Icon.Glyph(m_Glyph);
		Icon.IsTextScaleFactorEnabled(m_IsTextScaleFactorEnabled);
		Icon.MirroredWhenRightToLeft(m_MirroredWhenRightToLeft);
		if (m_Foreground) Icon.Foreground(m_Foreground);
		
		return Icon;
	}

	IInspectable FontIconExtension::ProvideValue(IXamlServiceProvider const&)
	{
		return ProvideValue();
	}

#pragma endregion
	
/* FontIcon properties */
#pragma region FontIcon properties

	muxm::FontFamily FontIconExtension::FontFamily()
	{
		return m_FontFamily;
	}

	void FontIconExtension::FontFamily(muxm::FontFamily Value)
	{
		m_FontFamily = Value;
	}

	double FontIconExtension::FontSize()
	{
		return m_FontSize;
	}

	void FontIconExtension::FontSize(double Value)
	{
		m_FontSize = Value;
	}

	wut::FontStyle FontIconExtension::FontStyle()
	{
		return m_FontStyle;
	}

	void FontIconExtension::FontStyle(wut::FontStyle Value)
	{
		m_FontStyle = Value;
	}

	wut::FontWeight FontIconExtension::FontWeight()
	{
		return m_FontWeight;
	}

	void FontIconExtension::FontWeight(wut::FontWeight Value)
	{
		m_FontWeight = Value;
	}

	hstring FontIconExtension::Glyph()
	{
		return m_Glyph;
	}

	void FontIconExtension::Glyph(hstring Value)
	{
		m_Glyph = Value;
	}

	bool FontIconExtension::IsTextScaleFactorEnabled()
	{
		return m_IsTextScaleFactorEnabled;
	}

	void FontIconExtension::IsTextScaleFactorEnabled(bool Value)
	{
		m_IsTextScaleFactorEnabled = Value;
	}

	bool FontIconExtension::MirroredWhenRightToLeft()
	{
		return m_MirroredWhenRightToLeft;
	}

	void FontIconExtension::MirroredWhenRightToLeft(bool Value)
	{
		m_MirroredWhenRightToLeft = Value;
	}

#pragma endregion
	
/* FontIcon properties inherited from IconElement */
#pragma region FontIcon properties inherited from IconElement

	muxm::Brush FontIconExtension::Foreground()
	{
		return m_Foreground;
	}
	
	void FontIconExtension::Foreground(muxm::Brush Value)
	{
		m_Foreground = Value;
	}

#pragma endregion
}