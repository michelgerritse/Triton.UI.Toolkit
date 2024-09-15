/*
 _____    _ _             _   _ ___ _____         _ _   _ _
|_   _| _(_) |_ ___ _ _  | | | |_ _|_   _|__  ___| | |_(_) |_
  | || '_| |  _/ _ \ ' \ | |_| || | _| |/ _ \/ _ \ | / / |  _|
  |_||_| |_|\__\___/_||_(_)___/|___(_)_|\___/\___/_|_\_\_|\__|

Copyright � 2024, Michel Gerritse
All rights reserved.

This source code is available under the BSD-3-Clause license.
See LICENSE.txt in the root directory of this source tree.

*/
#include "pch.h"
#include "WindowEx.h"

namespace winrt::Triton::UI::Windowing::implementation
{
	void WindowEx::AppWindowChangedEvent(IInspectable const& /* sender */, AppWindowChangedEventArgs const& e)
	{
		if (e.DidPresenterChange())
		{
			//TODO: Re-apply the overlapped presenter?
			//__debugbreak();
		}
	}
}