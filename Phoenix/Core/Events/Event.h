﻿#pragma once
#include <ostream>

#include "../Base/Base.h"

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

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4),
    };

    #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                    virtual EventType GetEventType() const override { return GetStaticType(); }\
                                    virtual const char* GetName() const override { return #type; }
    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual ~Event() = default;
        bool Handled = false;
        
        virtual EventType GetEventType() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        // ONLY FOR DEBUGGING
        virtual const char* GetName() const = 0;

        bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

   
}

