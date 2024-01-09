// WindowsInput.h

#pragma once
#include <vector>

#include "Utils/KeyCode.h"
#include "Utils/MouseCode.h"

namespace Phoenix
{
    class WindowsInput
    {
    public:
        static bool IsKeyPressed(KeyCode keyCode);
        static bool IsMouseButtonPressed(MouseCode mouseCode);
        static std::vector<float> GetMousePosition();

        static float GetMouseX();
        static float GetMouseY();
    };
}
