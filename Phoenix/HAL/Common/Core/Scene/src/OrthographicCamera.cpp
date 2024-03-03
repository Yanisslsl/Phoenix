      #include "../include/OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Phoenix
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -10.0f, 100.0f)), m_ViewMatrix(1.0f)
    {
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
        // view matrix is the inverse of the transform matrix, because the transformation applied to camera in the world space
        // need to be reversed to get the view matrix
        // eg: if the camera is moved 5 units to the right in the world space, the world space is moved 5 units to the left in the camera space
        // so the view matrix is the inverse of the transformation matrix, hence the inverse og a transformation matrix that moves 5 units to the right is a transformation matrix that moves 5 units to the left
        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        RecalculateViewMatrix();
    }

}