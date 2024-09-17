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
#include "Extensions.SymbolIconExtension.g.h"

using namespace winrt;

namespace muxc = Microsoft::UI::Xaml::Controls;
namespace muxm = Microsoft::UI::Xaml::Media;

namespace winrt::Triton::UI::Extensions::implementation
{
	struct SymbolIconExtension : SymbolIconExtensionT<SymbolIconExtension>
	{
		SymbolIconExtension() = default;

		/* MarkupExtension overrides */
		IInspectable ProvideValue();
		IInspectable ProvideValue(IXamlServiceProvider const&);

		/* SymbolIcon properties */
		muxc::Symbol Symbol();
		void Symbol(muxc::Symbol Value);

		/* SymbolIcon properties inherited from IconElement */
		muxm::Brush Foreground();
		void Foreground(muxm::Brush Value);

	private:
		muxc::Symbol m_Symbol{ muxc::Symbol::Emoji };
		muxm::Brush  m_Foreground{ nullptr };
	};
}

namespace winrt::Triton::UI::Extensions::factory_implementation
{
	struct SymbolIconExtension : SymbolIconExtensionT<SymbolIconExtension, implementation::SymbolIconExtension>
	{
	};
}