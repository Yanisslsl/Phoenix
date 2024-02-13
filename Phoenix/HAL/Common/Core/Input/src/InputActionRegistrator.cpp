#include "../include/InputActionRegistrator.h"

#include "Base/Base.h"
#include "Events/KeyEvent.h"
#include "Log/include/Log.h"


namespace Phoenix
{
    void InputActionRegistrator::RegisterAction(InputAction action, std::function<void()> callback)
    {
        if(m_InputActions.find(action) != m_InputActions.end())
        {
            PX_CORE_ASSERT(false, "Action already exists");
            return;
        }
        m_InputActions.emplace(std::make_pair(action, callback));
        m_InputActionsMap.emplace(std::make_pair(action.GetCode(), action));
    }

    void InputActionRegistrator::UnregisterAction(const InputAction action)
    {
        if(m_InputActions.find(action) == m_InputActions.end())
        {
            PX_CORE_ASSERT(false, "Action not found");
            return;
        }
        m_InputActions.erase(action);
    }

    

    void InputActionRegistrator::OnEvent(Event& e)
    {
        if(e.GetEventType() == EventType::KeyPressed)
        {
            auto& event = dynamic_cast<KeyPressedEvent&>(e);
            auto inputAction = m_InputActionsMap.find(event.GetKeyCode());
            if(inputAction != m_InputActionsMap.end())
            {
                m_InputActions[inputAction->second]();
            }
        }    
    }

}
