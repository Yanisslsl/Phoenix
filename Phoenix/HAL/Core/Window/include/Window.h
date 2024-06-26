﻿#pragma once
#include <cstdint>
#include <functional>
#include <string>

#include "Events/Event.h"


namespace Phoenix
{
    /** 
     * \brief WindowProps struct
     *        Used to store the properties of a Windows window
     */
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "Phoenix Engine",
                    uint32_t width = 1600,
                    uint32_t height = 900)
            : Title(title), Width(width), Height(height)
        {
        }
    };


    /** 
     * \brief WindowHal class, implements the WindowHal interface for Windows
     *        Used to create a Windows window
     */
    class WindowHal
    {
    public:
        virtual ~WindowHal() = default;
        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static std::unique_ptr<WindowHal> Create(const WindowProps& props = WindowProps());
    }; 
}

