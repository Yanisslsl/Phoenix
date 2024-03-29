﻿#include "../include/Window.h"
#include "../../../../Windows/Core/Window/include/Window.h"

namespace Phoenix
{
    // @TODO maybe have a global platform detector
    std::unique_ptr<WindowHal> WindowHal::Create(const WindowProps& props)
    {
        #ifdef PHOENIX_PLATFORM_WINDOWS
                return std::make_unique<Window>(props);
        #endif
    }
}

