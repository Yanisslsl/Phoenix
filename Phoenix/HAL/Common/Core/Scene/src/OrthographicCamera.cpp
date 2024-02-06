#include "../include/OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Phoenix
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -10.0f, 100.0f)), m_ViewMatrix(1.0f)
    {
        // glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // glm::mat4 view          = glm::mat4(1.0f);
        // glm::mat4 projection    = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(1280.0f/2, 720.0f/2, 0.0f));
        // model = glm::scale(model, glm::vec3(100.0f, 100.0f, 0.0f));
        // glm::matview  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // m_ViewProjectionMatrix =  projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f) * view * model;

        // m_ViewProjectionMatrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -10.f, 100.0f) * view * model;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

}