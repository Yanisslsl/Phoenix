// Input.h

#pragma once
#include <vector>

#include "Utils/KeyCode.h"
#include "Utils/MouseCode.h"

/**
 * @brief Input class for handling keyboard and mouse input.
 * @def will use internally the specific platform implementation.
 */
namespace Phoenix
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode keyCode);
        static bool IsMouseButtonPressed(MouseCode mouseCode);
        static std::vector<float> GetMousePosition();

        static float GetMouseX();
        static float GetMouseY();
    };
    
}
