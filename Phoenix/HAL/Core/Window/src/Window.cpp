#include "Core/Window/include/Window.h"
#include "Windows/Window/include/Window.h"

namespace Phoenix
{
    Scope<WindowHal> WindowHal::Create(const WindowProps& props)
    {
        #ifdef PHOENIX_PLATFORM_WINDOWS
                return std::make_unique<Window>(props);
        #endif
    }
}

