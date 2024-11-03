#include "../include/CameraController.h"

#include "Core/Input/include/Input.h"
#include "Events/EventDispatcher.h"


namespace Phoenix
{
    CameraController::CameraController(float left, float right, float bottom, float top, float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio),  m_Camera(left, right, bottom, top), m_Rotation(rotation)
    {
    }

    CameraController::CameraController(float fov, float width, float height, float nearClip, float farClip): m_AspectRatio(width/height), m_Camera(fov, width, height, nearClip, farClip), m_Rotation(false)
    {
    }

    void CameraController::OnUpdate(TimeStep ts)
    {
        if (Input::IsKeyPressed(Key::A))
        {
            m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(Key::D))
        {
            m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(Key::W))
        {
            m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(Key::S))
        {
            m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(Key::Q))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            if (Input::IsKeyPressed(Key::E))
                m_CameraRotation -= m_CameraRotationSpeed * ts;

            if (m_CameraRotation > 180.0f)
                m_CameraRotation -= 360.0f;
            else if (m_CameraRotation <= -180.0f)
                m_CameraRotation += 360.0f;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);

        m_CameraTranslationSpeed = m_ZoomLevel;
    }


    void CameraController::SetCameraPosition(const glm::vec3& position)
    {
        m_CameraPosition = position;
        m_Camera.SetPosition(m_CameraPosition);
    }
    
    void CameraController::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrolledEvent>(PX_BIND_EVENT_FN(CameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(CameraController::OnWindowResized));
    }

    bool CameraController::OnMouseScrolled(MouseScrolledEvent& event)
    {

        m_ZoomLevel -= event.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    void CameraController::OnResize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    bool CameraController::OnWindowResized(WindowResizeEvent& event)
    {

        OnResize((float)event.GetWidth(), (float)event.GetHeight());
        return false;
    }
}
