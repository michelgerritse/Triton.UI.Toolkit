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
#include "Extensions.FontIconExtension.g.h"

using namespace winrt;

namespace muxm = Microsoft::UI::Xaml::Media;
namespace wut  = Windows::UI::Text;

namespace winrt::Triton::UI::Extensions::implementation
{
	struct FontIconExtension : FontIconExtensionT<FontIconExtension>
	{
		FontIconExtension() = default;

		/* MarkupExtension overrides */
		IInspectable ProvideValue();
		IInspectable ProvideValue(IXamlServiceProvider const&);

		/* FontIcon properties */
		muxm::FontFamily FontFamily();
		void FontFamily(muxm::FontFamily Value);

		double FontSize();
		void FontSize(double Value);

		wut::FontStyle FontStyle();
		void FontStyle(wut::FontStyle Value);
		
		wut::FontWeight FontWeight();
		void FontWeight(wut::FontWeight Value);
		
		hstring Glyph();
		void Glyph(hstring Value);

		bool IsTextScaleFactorEnabled();
		void IsTextScaleFactorEnabled(bool Value);
		
		bool MirroredWhenRightToLeft();
		void MirroredWhenRightToLeft(bool Value);

		/* FontIcon properties inherited from IconElement */
		muxm::Brush Foreground();
		void Foreground(muxm::Brush Value);

	private:
		muxm::FontFamily m_FontFamily{ nullptr };
		double           m_FontSize{ 20.0 };
		wut::FontStyle   m_FontStyle{ wut::FontStyle::Normal };
		wut::FontWeight  m_FontWeight{ wut::FontWeights::Normal() };
		hstring          m_Glyph;
		bool             m_IsTextScaleFactorEnabled{ true };
		bool             m_MirroredWhenRightToLeft{ false };
		muxm::Brush      m_Foreground{ nullptr };
	};
}

namespace winrt::Triton::UI::Extensions::factory_implementation
{
	struct FontIconExtension : FontIconExtensionT<FontIconExtension, implementation::FontIconExtension>
	{
	};
}