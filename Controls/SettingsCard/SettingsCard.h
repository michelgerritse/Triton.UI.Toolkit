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
#include "Controls.SettingsCard.g.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Input;
using namespace Windows::Foundation;
using namespace Windows::System;

namespace winrt::Triton::UI::Controls::implementation
{
	struct SettingsCard : SettingsCardT<SettingsCard>
	{
	public:
		enum class PropertyItem : uint32_t
		{
			HeaderIcon,
			Header,
			Description,
			ActionIcon,
			ActionIconToolTip,
			IsActionIconVisible,
			IsClickEnabled,
			IsEnabled
		};
		
		SettingsCard();

		IInspectable HeaderIcon();
		void HeaderIcon(IInspectable const&);
		static DependencyProperty HeaderIconProperty() { return s_HeaderIconProperty; }
		
		IInspectable Header();
		void Header(IInspectable const&);
		static DependencyProperty HeaderProperty() { return s_HeaderProperty; }

		IInspectable Description();
		void Description(IInspectable const&);
		static DependencyProperty DescriptionProperty() { return s_DescriptionProperty; }

		IInspectable ActionIcon();
		void ActionIcon(IInspectable const&);
		static DependencyProperty ActionIconProperty() { return s_ActionIconProperty; }

		hstring ActionIconToolTip();
		void ActionIconToolTip(hstring const&);
		static DependencyProperty ActionIconToolTipProperty() { return s_ActionIconToolTipProperty; }

		bool IsActionIconVisible();
		void IsActionIconVisible(bool const&);
		static DependencyProperty IsActionIconVisibleProperty() { return s_IsActionIconVisibleProperty; }

		bool IsClickEnabled();
		void IsClickEnabled(bool const&);
		static DependencyProperty IsClickEnabledProperty() { return s_IsClickEnabledProperty; }
		
		void OnApplyTemplate();
		void OnPointerPressed(PointerRoutedEventArgs const&);
		void OnPointerReleased(PointerRoutedEventArgs const&);
		
	private:
		static DependencyProperty s_HeaderIconProperty;
		static DependencyProperty s_HeaderProperty;
		static DependencyProperty s_DescriptionProperty;
		static DependencyProperty s_ActionIconProperty;
		static DependencyProperty s_ActionIconToolTipProperty;
		static DependencyProperty s_IsActionIconVisibleProperty;
		static DependencyProperty s_IsClickEnabledProperty;

		bool VisualTreeReady{ false };
		bool IsFocussed{ false };

		event_token m_PointerEnteredToken;
		event_token m_PointerExitedToken;
		event_token m_PointerCaptureLostToken;
		event_token m_PointerCanceledToken;
		event_token m_PreviewKeyDownToken;
		event_token m_PreviewKeyUpToken;
		
		void OnPropertyChanged(PropertyItem const&);
		void EnableUserInteraction();
		void DisableUserInteraction();

		void PointerEnteredHandler(IInspectable const&, PointerRoutedEventArgs const&);
		void PointerExitedHandler(IInspectable const&, PointerRoutedEventArgs const&);
		void PointerCaptureLostHandler(IInspectable const&, PointerRoutedEventArgs const&);
		void PointerCanceledHandler(IInspectable const&, PointerRoutedEventArgs const&);
		void PreviewKeyDownHandler(IInspectable const&, KeyRoutedEventArgs const&);
		void PreviewKeyUpHandler(IInspectable const&, KeyRoutedEventArgs const&);
	};
}
namespace winrt::Triton::UI::Controls::factory_implementation
{
	struct SettingsCard : SettingsCardT<SettingsCard, implementation::SettingsCard>
	{
	};
}