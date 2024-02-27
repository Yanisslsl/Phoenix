// WindowsInput.h

#pragma once
#include <vector>

#include "Utils/KeyCode.h"
#include "Utils/MouseCode.h"
#include "Core.h"

namespace Phoenix
{
    class PHOENIX_API WindowsInput
    {
    public:
        [[ nodiscard]] static bool IsKeyPressed(KeyCode keyCode);
        [[ nodiscard]] static bool IsMouseButtonPressed(MouseCode mouseCode);
        [[ nodiscard]] static std::vector<float> GetMousePosition();

        [[ nodiscard]] static float GetMouseX();
        [[ nodiscard]] static float GetMouseY();
    };
}
