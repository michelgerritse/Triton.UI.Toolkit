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
#include "Extensions/BitmapIconExtension.g.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation;

namespace muxm = Microsoft::UI::Xaml::Media;
namespace wf   = Windows::Foundation;

namespace winrt::Triton::UI::Extensions::implementation
{
	struct BitmapIconExtension : BitmapIconExtensionT<BitmapIconExtension>
	{
		BitmapIconExtension() = default;

		/* MarkupExtension overrides */
		IInspectable ProvideValue();
		IInspectable ProvideValue(IXamlServiceProvider const&);

		/* BitmapIcon properties */
		bool ShowAsMonochrome();
		void ShowAsMonochrome(bool Value);

		wf::Uri UriSource();
		void UriSource(wf::Uri Value);

		/* BitmapIcon properties inherited from IconElement */
		muxm::Brush Foreground();
		void Foreground(muxm::Brush Value);

	private:
		bool        m_ShowAsMonochrome{ true };
		wf::Uri     m_UriSource{ nullptr };
		muxm::Brush m_Foreground{ nullptr };
	};
}

namespace winrt::Triton::UI::Extensions::factory_implementation
{
	struct BitmapIconExtension : BitmapIconExtensionT<BitmapIconExtension, implementation::BitmapIconExtension>
	{
	};
}