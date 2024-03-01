// InputActions.h

#pragma once
#include <string>

#include "Core.h"
#include "Utils/MouseCode.h"
#include "Utils/KeyCode.h"


namespace Phoenix
{
    class PHOENIX_API InputAction
    {
    public:
        InputAction() = delete;
        InputAction(std::string name, uint16_t code) : m_Name(name), m_Code(code) {}
        [[nodiscard]] std::string GetName() const { return m_Name; }
        [[nodiscard]] uint16_t GetCode() const { return m_Code; }
        bool operator < (const InputAction& action) const
        {
            //  FIX: Error C2678 : '<' binaire : aucun opérateur trouvé qui accepte un opérande de partie gauche de type 'const _Ty' (ou il n'existe pas de conversion acceptable)
            return m_Name < action.m_Name;
        } 
    private:
        uint16_t m_Code;
        std::string m_Name;
    };

    class PHOENIX_API MouseInputAction: public InputAction
    {
    public:
        MouseInputAction() = delete;
        MouseInputAction(std::string name, const MouseCode mouseCode)
            : InputAction(name, mouseCode) {}
    };

    class PHOENIX_API KeyInputAction: public InputAction
    {
    public:
        KeyInputAction() = delete;
        KeyInputAction(std::string name, const KeyCode keyCode)
            : InputAction(name, keyCode) {}
    private:
    };
}
