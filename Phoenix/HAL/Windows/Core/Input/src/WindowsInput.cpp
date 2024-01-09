#include "../include/WindowsInput.h"

#include "Windows/Core/Application/include/Application.h"
#include "Windows/Core/Window/include/Window.h"


namespace Phoenix
{
    bool WindowsInput::IsKeyPressed(KeyCode keyCode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(keyCode));
        return state == GLFW_PRESS;
    }

    bool WindowsInput::IsMouseButtonPressed(MouseCode mouseCode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseCode));
        return state == GLFW_PRESS;
    }

    std::vector<float> WindowsInput::GetMousePosition()
    {
        auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }

    float WindowsInput::GetMouseX()
    {
        return GetMousePosition()[0];
    }

    float WindowsInput::GetMouseY()
    {
        return GetMousePosition()[1];
    }

}

