﻿#pragma once
#include "Event.h"
#include <functional>


namespace Phoenix
{
    // NOTE: Maybe pass the system to an queue based dispatcher ?
    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_event(event)
        {
        }

        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.Handled |= func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }

        inline std::ostream& operator<<(std::ostream& os, const Event& e)
        {
            return os << e.ToString();
        }

        private :
            Event& m_event;
    };
}
