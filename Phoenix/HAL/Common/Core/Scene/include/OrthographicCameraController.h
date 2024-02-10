// OrthographicCameraController.h

#pragma once
#include "OrthographicCamera.h"
#include "../../../Core/Core.h"
#include "../../../Core/Events/Event.h"
#include "../../../Core/Events/MouseEvent.h"
#include "../../../Core/Events/WindowEvent.h"
#include "../../Core/Utils/TimeStep.h"


namespace Phoenix
{
    class PHOENIX_API OrthographicCameraController
    {
    public:
        // @TODO change all constructors to explicit ones
        explicit OrthographicCameraController(float left, float right, float bottom, float top, float aspectRation, bool rotation = false);
        void OnUpdate(TimeStep ts);
        void OnEvent(Event& event);

        void OnResize(float width, float height);


        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& event);
        bool OnWindowResized(WindowResizeEvent& event);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };
}
