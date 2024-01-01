#pragma once
#include <GLFW/glfw3.h>

#include "Common/Core/Window/include/Window.h"


namespace Phoenix {

    class Window : public WindowHal
    {
    public:
        Window(const WindowProps& props);
        virtual ~Window();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        void InitGLFWCallbacks();

        // Window attributes
        void SetEventCallback(const std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void* GetNativeWindow() const { return m_Window; }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            // DOC : EventCallback is a function that takes an Event reference and returns void
            // with SetEventCallback, we can set the callback function to be called when an event occurs, and dispatch the event in this callback
            std::function<void(Event&)> EventCallback;
        };

        WindowData m_Data;
    };

}
