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
#include "SymbolIconExtension.h"
#include "Extensions.SymbolIconExtension.g.cpp"

/* References:
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.markup.markupextension
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.controls.symbolicon
	https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.controls.iconelement
*/

namespace winrt::Triton::UI::Extensions::implementation
{
/* MarkupExtension overrides */
#pragma region MarkupExtension overrides

	IInspectable SymbolIconExtension::ProvideValue()
	{
		SymbolIcon Icon;

		Icon.Symbol(m_Symbol);
		if (m_Foreground) Icon.Foreground(m_Foreground);
		
		return Icon;
	}

	IInspectable SymbolIconExtension::ProvideValue(IXamlServiceProvider const&)
	{
		return ProvideValue();
	}

#pragma endregion
	
/* SymbolIcon properties */
#pragma region SymbolIcon properties

	muxc::Symbol SymbolIconExtension::Symbol()
	{
		return m_Symbol;
	}

	void SymbolIconExtension::Symbol(muxc::Symbol Value)
	{
		m_Symbol = Value;
	}

#pragma endregion
	
/* SymbolIcon properties inherited from IconElement */
#pragma region SymbolIcon properties inherited from IconElement

	muxm::Brush SymbolIconExtension::Foreground()
	{
		return m_Foreground;
	}
	
	void SymbolIconExtension::Foreground(muxm::Brush Value)
	{
		m_Foreground = Value;
	}

#pragma endregion
}