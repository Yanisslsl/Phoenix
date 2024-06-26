#pragma once
#include "Camera.h"
#include "Core.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"
#include "Utils/TimeStep.h"

namespace Phoenix
{
    /**
     * \brief Orthographic camera controller
     *        Used for controlling the orthographic camera in the game.
     */
    class PHOENIX_API CameraController
    {
    public:
        /**
         * \brief Orthographic camera controller constructor
         * \param aspectRation
         * \param rotation
         */
        explicit CameraController(float left, float right, float bottom, float top, float aspectRation, bool rotation);

        explicit CameraController(float fov, float width, float height, float nearClip, float farClip);

        /**
         * \brief OnUpdate listener
         * \param ts TimeStep
         */
        void OnUpdate(TimeStep ts);

        /**
         * \brief OnEvent listener
         * \param event Event
         */
        void OnEvent(Event& event);

        /**
         * \brief OnResize listener
         * \param width Width
         * \param height Height
         */
        void OnResize(float width, float height);
        /**
         * \brief Get the camera
         * \return Camera
         */
         Camera& GetCamera()
         {
           return m_Camera;
         }
         const Camera& GetCamera() const
         {
           return m_Camera;
         }

        /**
         * \brief Get the zoom level
         * \return float Zoom level
         */
        float GetZoomLevel() const { return m_ZoomLevel; }

        /**
         * \brief Set the zoom level
         * \param level Zoom level
         */
        void SetZoomLevel(float level) { m_ZoomLevel = level; }

        /** \brief Set the camera position
         * \param position Position to set
         */
        void SetCameraPosition(const glm::vec3& position);

         /** \brief Get the camera position
         * \return glm::vec2
         */
        glm::vec2 GetCameraPosition() const { return { m_CameraPosition.x, m_CameraPosition.y }; }
    private:
        /** \brief OnMouseScrolled listener
         * \param event MouseScrolledEvent
         * \return bool
         */
        bool OnMouseScrolled(MouseScrolledEvent& event);

        /** \brief OnWindowResized listener
         * \param event WindowResizeEvent
         * \return bool
         */
        bool OnWindowResized(WindowResizeEvent& event);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        Camera m_Camera;
        bool m_Rotation;
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };
}
