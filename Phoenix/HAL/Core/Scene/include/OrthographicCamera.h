#pragma once
#include "glm/glm.hpp"
#include "Core.h"

namespace Phoenix
{
    /**
     * \brief OrthographicCamera class that represent an orthographic camera in the game.
     *        Used for rendering 2D scenes.
     */
    class PHOENIX_API OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        /**
         * \brief Set the projection matrix
         * \param left Left value
         * \param right Right value
         * \param bottom Bottom value
         * \param top Top value
         */
        void SetProjection(float left, float right, float bottom, float top);

        /**
         * \brief Get the position of the camera
         * \return glm::vec3
         */
        const glm::vec3& GetPosition() const { return m_Position; }


        /**
         * \brief Set the position of the camera
         * \param position Position to set
         */
        void SetPosition(const glm::vec3& position);

        /**
         * \brief Get the rotation of the camera
         * \return float
         */
        float GetRotation() const { return m_Rotation; }

        /**
         * \brief Set the rotation of the camera
         * \param rotation Rotation to set
         */
        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }


        /**
         * \brief Get the projection matrix
         * \return glm::mat4
         */
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

        /**
         * \brief Get the view matrix
         * \return glm::mat4
         */
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

        /**
         * \brief Get the view projection matrix
         * \return glm::mat4
         */
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    private:

        /**
         * \brief Recalculate the view matrix
         */
        void RecalculateViewMatrix();
    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;
    };
}
