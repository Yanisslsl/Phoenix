// InputActionRegistrator.h

#pragma once
#include <functional>
#include <map>
#include <string>

#include "InputActions.h"
#include "../../../Core/Core.h"
#include "../../Core/Events/Event.h"

namespace Phoenix
{
    class PHOENIX_API InputActionRegistrator
    {
    public:
        InputActionRegistrator() = default;
        void RegisterAction(const InputAction action, const std::function<void()>& callback);
        void UnregisterAction(const InputAction action);
        void OnEvent(Event& e);
    private:
        std::map<InputAction, std::function<void()>&> m_InputActions;
        std::function<void()> m_Callback;
    };
}
