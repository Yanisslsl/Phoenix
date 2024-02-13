#include "../include/InputActionRegistrator.h"

#include "Base/Base.h"
#include "Log/include/Log.h"


namespace Phoenix
{
    void InputActionRegistrator::RegisterAction(const InputAction action, const std::function<void()>& callback)
    {
        if(m_InputActions.find(action.GetName()) == m_InputActions.end())
        {
            PX_CORE_ASSERT(false, "Action already registered");
            return;
        }
        m_InputActions[action] = callback;
    }

    void InputActionRegistrator::UnregisterAction(const InputAction action)
    {
        if(m_InputActions.find(action.GetName()) == m_InputActions.end())
        {
            PX_CORE_ASSERT(false, "Action not found");
            return;
        }
        m_InputActions.erase(action.GetName());
    }

    void InputActionRegistrator::OnEvent(Event& e)
    {
        // for(const auto input: m_InputActions)
        // {
        //     
        // }
    }

}
