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
#include "SettingsCard.h"
#include "Controls/SettingsCard.g.cpp"

/* Element name definitions, make sure this is consistent with the XAML naming */
constexpr auto HeaderIconElementName  = L"HeaderIconElement";
constexpr auto HeaderElementName      = L"HeaderElement";
constexpr auto DescriptionElementName = L"DescriptionElement";
constexpr auto ActionIconElementName  = L"ActionIconElement";

/* Visual state definitions, make sure this is consistent with the XAML naming */
constexpr auto NormalState      = L"Normal";
constexpr auto PointerOverState = L"PointerOver";
constexpr auto PressedState     = L"Pressed";
constexpr auto DisabledState    = L"Disabled";

namespace winrt::Triton::UI::Controls::implementation
{	
	SettingsCard::SettingsCard()
	{
		DefaultStyleKey(box_value(L"Triton.UI.Controls.SettingsCard"));
	}

	void SettingsCard::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		
		/* Mark visual tree ready */
		VisualTreeReady = true;

		/* Set initial property item states */
		OnPropertyChanged(PropertyItem::HeaderIcon);
		OnPropertyChanged(PropertyItem::Header);
		OnPropertyChanged(PropertyItem::Description);
		OnPropertyChanged(PropertyItem::ActionIcon);
		OnPropertyChanged(PropertyItem::IsClickEnabled);
		OnPropertyChanged(PropertyItem::IsEnabled);

		/* Register IsEnabledChanged event callback handler */
		IsEnabledChanged([](auto Sender, auto)
			{
				auto Projection = Sender.as<Triton::UI::Controls::SettingsCard>();
				get_self<SettingsCard>(Projection)->OnPropertyChanged(PropertyItem::IsEnabled);
			});

		/* Register GettingFocus event callback handler */
		GettingFocus([](auto Sender, auto)
			{
				auto Projection = Sender.as<Triton::UI::Controls::SettingsCard>();
				get_self<SettingsCard>(Projection)->IsFocussed = true;
			});

		/* Register LosingFocus event callback handler */
		LosingFocus([](auto Sender, auto)
			{
				auto Projection = Sender.as<Triton::UI::Controls::SettingsCard>();
				get_self<SettingsCard>(Projection)->IsFocussed = false;
			});
	}

	void SettingsCard::OnPointerPressed(PointerRoutedEventArgs const& Args)
	{
		if (IsClickEnabled())
		{
			base_type::OnPointerPressed(Args);
			VisualStateManager::GoToState(*this, PressedState, true);
		}
	}

	void SettingsCard::OnPointerReleased(PointerRoutedEventArgs const& Args)
	{
		if (IsClickEnabled())
		{
			base_type::OnPointerReleased(Args);
			VisualStateManager::GoToState(*this, NormalState, true);
		}
	}

	void SettingsCard::OnPropertyChanged(PropertyItem const& Item)
	{
		if (!VisualTreeReady) return;

		switch (Item)
		{
		case PropertyItem::HeaderIcon:
			if (auto HeaderIconElement = GetTemplateChild(HeaderIconElementName).try_as<FrameworkElement>())
			{
				HeaderIconElement.Visibility(Header() ? Visibility::Visible : Visibility::Collapsed);
			}
			break;

		case PropertyItem::Header:
			if (auto HeaderElement = GetTemplateChild(HeaderElementName).try_as<FrameworkElement>())
			{
				HeaderElement.Visibility(Header() ? Visibility::Visible : Visibility::Collapsed);
			}
			break;

		case PropertyItem::Description:
			if (auto DescriptionElement = GetTemplateChild(DescriptionElementName).try_as<FrameworkElement>())
			{
				DescriptionElement.Visibility(Description() ? Visibility::Visible : Visibility::Collapsed);
			}
			break;

		case PropertyItem::ActionIcon:
			if (auto ActionIconElement = GetTemplateChild(ActionIconElementName).try_as<FrameworkElement>())
			{
				if (IsClickEnabled() && IsActionIconVisible())
				{
					ActionIconElement.Visibility(Visibility::Visible);
				}
				else
				{
					ActionIconElement.Visibility(Visibility::Collapsed);
				}
			}
			break;

		case PropertyItem::IsClickEnabled:
			OnPropertyChanged(PropertyItem::ActionIcon);

			if (IsClickEnabled() && IsEnabled())
			{
				EnableUserInteraction();
			}
			else
			{
				DisableUserInteraction();
			}
			break;

		case PropertyItem::IsEnabled:
			VisualStateManager::GoToState(*this, IsEnabled() ? NormalState : DisabledState, true);
			break;
		}
	}

	void SettingsCard::EnableUserInteraction()
	{
		IsTabStop(true);

		/* Register pointer event handlers */
		m_PointerEnteredToken     = PointerEntered(    { this, &SettingsCard::PointerEnteredHandler     });
		m_PointerExitedToken      = PointerExited(     { this, &SettingsCard::PointerExitedHandler      });
		m_PointerCaptureLostToken = PointerCaptureLost({ this, &SettingsCard::PointerCaptureLostHandler });
		m_PointerCanceledToken    = PointerCanceled(   { this, &SettingsCard::PointerCanceledHandler    });
		
		/* Register key event handlers */
		m_PreviewKeyDownToken     = PreviewKeyDown(    { this, &SettingsCard::PreviewKeyDownHandler     });
		m_PreviewKeyUpToken       = PreviewKeyUp(      { this, &SettingsCard::PreviewKeyUpHandler       });
	}

	void SettingsCard::DisableUserInteraction()
	{
		IsTabStop(false);

		/* Unregister pointer event handlers */
		PointerEntered(m_PointerEnteredToken);
		PointerExited(m_PointerExitedToken);
		PointerCaptureLost(m_PointerCaptureLostToken);
		PointerCanceled(m_PointerCanceledToken);

		/* Unregister key event handlers */
		PreviewKeyDown(m_PreviewKeyDownToken);
		PreviewKeyUp(m_PreviewKeyUpToken);
	}

	void SettingsCard::PointerEnteredHandler(IInspectable const&, PointerRoutedEventArgs const& Args)
	{
		base_type::OnPointerEntered(Args);
		VisualStateManager::GoToState(*this, PointerOverState, true);
	}

	void SettingsCard::PointerExitedHandler(IInspectable const&, PointerRoutedEventArgs const& Args)
	{
		base_type::OnPointerExited(Args);
		VisualStateManager::GoToState(*this, NormalState, true);
	}

	void SettingsCard::PointerCaptureLostHandler(IInspectable const&, PointerRoutedEventArgs const& Args)
	{
		base_type::OnPointerCaptureLost(Args);
		VisualStateManager::GoToState(*this, NormalState, true);
	}

	void SettingsCard::PointerCanceledHandler(IInspectable const&, PointerRoutedEventArgs const& Args)
	{
		base_type::OnPointerCanceled(Args);
		VisualStateManager::GoToState(*this, NormalState, true);
	}

	void SettingsCard::PreviewKeyDownHandler(IInspectable const&, KeyRoutedEventArgs const& Args)
	{
		auto Key = Args.Key();
		
		if ((Key == VirtualKey::Enter) || (Key == VirtualKey::Space) || (Key == VirtualKey::GamepadA))
		{
			if (IsFocussed)
			{
				VisualStateManager::GoToState(*this, PressedState, true);
			}
		}
	}

	void SettingsCard::PreviewKeyUpHandler(IInspectable const&, KeyRoutedEventArgs const& Args)
	{
		auto Key = Args.Key();

		if ((Key == VirtualKey::Enter) || (Key == VirtualKey::Space) || (Key == VirtualKey::GamepadA))
		{
			VisualStateManager::GoToState(*this, NormalState, true);
		}
	}
}