#include "Core/Input/include/Input.h"
#include "Windows/Input/include/WindowsInput.h"

namespace Phoenix
{
    bool Input::IsKeyPressed(KeyCode keyCode)
    {
        #ifdef PHOENIX_PLATFORM_WINDOWS
                return WindowsInput::IsKeyPressed(keyCode);
        #endif
    }

    bool Input::IsMouseButtonPressed(MouseCode mouseCode)
    {
        #ifdef PHOENIX_PLATFORM_WINDOWS
                return WindowsInput::IsMouseButtonPressed(mouseCode);
        #endif
    }

    std::vector<float> Input::GetMousePosition()
    {
        #ifdef PHOENIX_PLATFORM_WINDOWS
                return WindowsInput::GetMousePosition();
        #endif
    }

    float Input::GetMouseX()
    {
        return GetMousePosition()[0];
    }

    float Input::GetMouseY()
    {
        return GetMousePosition()[1];
    }
}
