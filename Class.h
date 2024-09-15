#pragma once

#include "Class.g.h"

namespace winrt::Triton_UI_Toolkit::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::Triton_UI_Toolkit::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
