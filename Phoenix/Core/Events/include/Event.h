#pragma once
#include <ostream>

#include "../../Base/Base.h"

namespace Phoenix
{
    enum class EventType
    {
        None,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4),
    };
    
    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        // ONLY FOR DEBUGGING
        virtual const char* GetName() const = 0;
        virtual const char* GetEventType() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }
    };

   
}

