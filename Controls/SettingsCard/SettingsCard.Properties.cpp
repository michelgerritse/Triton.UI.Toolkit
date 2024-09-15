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

namespace winrt::Triton::UI::Controls::implementation
{
/* Dependency property: HeaderIcon */
#pragma region HeaderIconProperty
	
	/* Register property */
	DependencyProperty SettingsCard::s_HeaderIconProperty =
		DependencyProperty::Register(
			L"HeaderIcon",
			xaml_typename<IInspectable>(),
			xaml_typename<Triton::UI::Controls::SettingsCard>(),
			PropertyMetadata{ 
				nullptr, 
				[](auto Sender, auto)
				{
					auto Projection = Sender.as<Triton::UI::Controls::SettingsCard>();
					get_self<SettingsCard>(Projection)->OnPropertyChanged(PropertyItem::HeaderIcon);
				}
			}
		);

	/* Get property */
	IInspectable SettingsCard::HeaderIcon()
	{
		return GetValue(s_HeaderIconProperty);
	}

	/* Set property */
	void SettingsCard::HeaderIcon(IInspectable const& Value)
	{
		SetValue(s_HeaderIconProperty, Value);
	}

#pragma endregion
	
/* Dependency property: Header */
#pragma region HeaderProperty

	/* Register property */
	DependencyProperty SettingsCard::s_HeaderProperty =
		DependencyProperty::Register(
			L"Header",
			xaml_typename<IInspectable>(),
			xaml_typename<Triton::UI::Controls::SettingsCard>(),
			PropertyMetadata{
				nullptr,
				[](auto Sender, auto)
				{
					auto Projection = Sender.as<Triton::UI::Controls::SettingsCard>();
					get_self<SettingsCard>(Projection)->OnPropertyChanged(PropertyItem::Header);
				}
			}
		);

	/* Get property */
	IInspectable SettingsCard::Header()
	{
		return GetValue(s_HeaderProperty);
	}

	/* Set property */
	void SettingsCard::Header(IInspectable const& Value)
	{
		SetValue(s_HeaderProperty, Value);
	}

#pragma endregion

/* Dependency property: Description */
#pragma region DescriptionProperty

	/* Register property */
	DependencyProperty SettingsCard::s_DescriptionProperty =
		DependencyProperty::Register(
			L"Description",
			xaml_typename<IInspectable>(),
			xaml_typename<Triton::UI::Controls::SettingsCard>(),
			PropertyMetadata{
				nullptr,
				[](auto Sender, auto)
				{
					auto Projection = Sender.as<Triton::UI::Controls::SettingsCard>();
					get_self<SettingsCard>(Projection)->OnPropertyChanged(PropertyItem::Description);
				}
			}
		);

	/* Get property */
	IInspectable SettingsCard::Description()
	{
		return GetValue(s_DescriptionProperty);
	}

	/* Set property */
	void SettingsCard::Description(IInspectable const& Value)
	{
		SetValue(s_DescriptionProperty, Value);
	}

#pragma endregion

/* Dependency property: ActionIcon */
#pragma region ActionIconProperty

	/* Register property */
	DependencyProperty SettingsCard::s_ActionIconProperty =
		DependencyProperty::Register(
			L"ActionIcon",
			xaml_typename<IInspectable>(),
			xaml_typename<Triton::UI::Controls::SettingsCard>(),
			PropertyMetadata{ box_value(L"\xE974") }
		);

	/* Get property */
	IInspectable SettingsCard::ActionIcon()
	{
		return GetValue(s_ActionIconProperty);
	}

	/* Set property */
	void SettingsCard::ActionIcon(IInspectable const& Value)
	{
		SetValue(s_ActionIconProperty, Value);
	}

#pragma endregion

/* Dependency property: ActionIconToolTip */
#pragma region ActionIconToolTipProperty

	/* Register property */
	DependencyProperty SettingsCard::s_ActionIconToolTipProperty =
		DependencyProperty::Register(
			L"ActionIconToolTip",
			xaml_typename<hstring>(),
			xaml_typename<Triton::UI::Controls::SettingsCard>(),
			PropertyMetadata{ nullptr }
		);

	/* Get property */
	hstring SettingsCard::ActionIconToolTip()
	{
		return unbox_value<hstring>(GetValue(s_ActionIconToolTipProperty));
	}

	/* Set property */
	void SettingsCard::ActionIconToolTip(hstring const& Value)
	{
		SetValue(s_ActionIconToolTipProperty, box_value(Value));
	}

#pragma endregion

/* Dependency property: IsActionIconVisible */
#pragma region IsActionIconVisibleProperty

	/* Register property */
	DependencyProperty SettingsCard::s_IsActionIconVisibleProperty =
		DependencyProperty::Register(
			L"IsActionIconVisible",
			xaml_typename<bool>(),
			xaml_typename<Triton::UI::Controls::SettingsCard>(),
			PropertyMetadata{
				box_value<bool>(true),
				[](auto Sender, auto)
				{
					auto Projection = Sender.as<Triton::UI::Controls::SettingsCard>();
					get_self<SettingsCard>(Projection)->OnPropertyChanged(PropertyItem::ActionIcon);
				}
			}
		);

	/* Get property */
	bool SettingsCard::IsActionIconVisible()
	{
		return unbox_value<bool>(GetValue(s_IsActionIconVisibleProperty));
	}

	/* Set property */
	void SettingsCard::IsActionIconVisible(bool const& Value)
	{
		SetValue(s_IsActionIconVisibleProperty, box_value<bool>(Value));
	}

#pragma endregion

/* Dependency property: IsClickEnabled */
#pragma region IsClickEnabledProperty

	/* Register property */
	DependencyProperty SettingsCard::s_IsClickEnabledProperty =
		DependencyProperty::Register(
			L"IsClickEnabled",
			xaml_typename<bool>(),
			xaml_typename<Triton::UI::Controls::SettingsCard>(),
			PropertyMetadata{
				box_value<bool>(false),
				[](auto Sender, auto)
				{
					auto Projection = Sender.as<Triton::UI::Controls::SettingsCard>();
					get_self<SettingsCard>(Projection)->OnPropertyChanged(PropertyItem::IsClickEnabled);
				}
			}
		);

	/* Get property */
	bool SettingsCard::IsClickEnabled()
	{
		return unbox_value<bool>(GetValue(s_IsClickEnabledProperty));
	}

	/* Set property */
	void SettingsCard::IsClickEnabled(bool const& Value)
	{
		SetValue(s_IsClickEnabledProperty, box_value<bool>(Value));
	}

#pragma endregion
}