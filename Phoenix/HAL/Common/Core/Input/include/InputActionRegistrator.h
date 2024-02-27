// InputActionRegistrator.h
#pragma once
#include <functional>
#include <map>
#include "InputActions.h"
#include "Core.h"
#include "Events/Event.h"

namespace Phoenix
{
    class PHOENIX_API InputActionRegistrator
    {
    public:
        InputActionRegistrator() = default;
        void RegisterAction(const InputAction action, std::function<void()> callback);
        void UnregisterAction(const InputAction action);
        void OnEvent(Event& e);
        void OnInputAction();
    private:
        std::map<InputAction, std::function<void()>> m_InputActions;
        // maybe an InputAction can have multiple keys or mouse buttons
        std::map<uint16_t, InputAction> m_InputActionsMap;
    };
}



