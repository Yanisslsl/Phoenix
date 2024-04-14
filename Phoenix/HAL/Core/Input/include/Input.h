// Input.h

#pragma once
#include <vector>

#include "../../../Core/Utils/KeyCode.h"
#include "../../../Core/Utils/MouseCode.h"
#include "../../../Core/Core.h"

namespace Phoenix
{
   /**
    * @brief Input class for handling keyboard and mouse input.
    * @def will use internally the specific platform implementation.
    */
    class PHOENIX_API Input
    {
    public:
        /**
         * \brief Check if a key is pressed
         * \param keyCode Key to check 
         * \return whether the key is pressed or not
         */
        [[ nodiscard]] static bool IsKeyPressed(KeyCode keyCode);

        /**
         * \brief Check if a mouse button is pressed
         * \param mouseCode Mouse button to check
         * \return whether the mouse button is pressed or not
         */
        [[ nodiscard]] static bool IsMouseButtonPressed(MouseCode mouseCode);

        /**
         * \brief Get the mouse position
         * \return the mouse position
         */
        [[ nodiscard]] static std::vector<float> GetMousePosition();


        /**
         * \brief Get the mouse x position
         * \return the mouse x position
         */
        [[ nodiscard]] static float GetMouseX();

        /**
         * \brief Get the mouse y position
         * \return the mouse y position
         */
        [[ nodiscard]] static float GetMouseY();
    };
    
}
