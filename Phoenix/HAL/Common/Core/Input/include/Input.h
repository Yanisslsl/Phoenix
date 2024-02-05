// Input.h

#pragma once
#include <vector>

#include "../../../Core/Utils/KeyCode.h"
#include "../../../Core/Utils/MouseCode.h"
#include "../../../Core/Core.h"

/**
 * @brief Input class for handling keyboard and mouse input.
 * @def will use internally the specific platform implementation.
 */
namespace Phoenix
{
    class PHOENIX_API Input
    {
    public:
        [[ nodiscard]] static bool IsKeyPressed(KeyCode keyCode);
        [[ nodiscard]] static bool IsMouseButtonPressed(MouseCode mouseCode);
        [[ nodiscard]] static std::vector<float> GetMousePosition();

        [[ nodiscard]] static float GetMouseX();
        [[ nodiscard]] static float GetMouseY();
    };
    
}
