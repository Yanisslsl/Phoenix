// InputActions.h

#pragma once
#include <string>

#include "../../../Core/Core.h"
#include "Utils/KeyCode.h"
#include "Utils/MouseCode.h"


namespace Phoenix
{
    class PHOENIX_API InputAction
    {
    public:
        InputAction() = delete;
        InputAction(std::string name) : m_Name(name) {}
        [[nodiscard]] std::string GetName() const { return m_Name; }
    private:
        std::string m_Name;
    };

    class PHOENIX_API MouseInputAction: public InputAction
    {
    public:
        MouseInputAction() = delete;
        MouseInputAction(std::string name, const MouseCode mouseCode)
            : m_mouseCode(mouseCode), InputAction(name) {}
        [[nodiscard]] MouseCode GetMouseCode() const { return m_mouseCode; }
    private:
        MouseCode m_mouseCode;
    };

    class PHOENIX_API KeyInputAction: public InputAction
    {
    public:
        KeyInputAction() = delete;
        KeyInputAction(std::string name, const KeyCode keyCode)
            : m_keyCode(keyCode), InputAction(name) {}
        [[nodiscard]] KeyCode GetKeyCode() const { return m_keyCode; }
    private:
        KeyCode m_keyCode;
    };
}
