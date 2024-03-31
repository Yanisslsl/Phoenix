// InputActionRegistrator.h
#pragma once
#include <functional>
#include <map>
#include "InputActions.h"
#include "Core.h"
#include "Events/Event.h"

namespace Phoenix
{
    /**
     * \brief
     * @TODO: the system is a bit closed now, if a new controller is added, the system needs to be updated.
     * Maybe add a file that binds 
     */
    class PHOENIX_API InputActionRegistratorSubSystem
    {
    public:
        InputActionRegistratorSubSystem() = default;
        /**
         * \brief Register an action with a callback
         * \param action
         * \param callback
         */
        void RegisterAction(const InputAction action, std::function<void()> callback);

        /**
         * \brief Unregister an action
         * \param action
         */
        void UnregisterAction(const InputAction action);


        /**
         * \brief OnEvent listener
         * \param e Event   
         */
        void OnEvent(Event& e);
    private:
        //same for callbks
        std::map<InputAction, std::function<void()>> m_InputActions;
        // maybe an InputAction can have multiple keys or mouse buttons
        std::map<uint16_t, InputAction> m_InputActionsMap;
        
    };
}



