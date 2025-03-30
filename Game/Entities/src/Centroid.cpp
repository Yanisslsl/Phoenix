#include "../include/Centroid.h"


#include "../include/Boid.h"

#include <iostream>
#include <glm/ext/scalar_constants.hpp>

#include "Core/Application/include/Application.h"
#include "Core/ECSExtended/include/TransformSubsytem.h"
#include "Utils/Timer.h"

Centroid::Centroid()

{
    float height = 2.0f; int segments = 16;
        std::vector<float> vertices;
        std::vector<uint32_t> indices;
        vertices.push_back(0.0f);    // x
        vertices.push_back(height);  // y
        vertices.push_back(0.0f);    // z
        vertices.push_back(0.5f);    // u
        vertices.push_back(0.0f);    // v
        
        vertices.push_back(0.0f);    // x
        vertices.push_back(0.0f);    // y
        vertices.push_back(0.0f);    // z
        vertices.push_back(0.5f);    // u
        vertices.push_back(1.0f);    // v
        
        for (int i = 0; i < segments; i++) {
            float M_PI = 3.14159265359f;
            float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
            float x = cos(angle);
            float z = sin(angle);
            
            vertices.push_back(x);                      // x
            vertices.push_back(0.0f);                   // y
            vertices.push_back(z);                      // z
            vertices.push_back(0.5f + 0.5f * x);        // u
            vertices.push_back(1.0f - 0.5f * z);        // v
        }
        
        for (int i = 0; i < segments; i++) {
            indices.push_back(0);
            indices.push_back(2 + i);
            indices.push_back(2 + ((i + 1) % segments));
        }
        
        for (int i = 0; i < segments; i++) {
            indices.push_back(1);
            indices.push_back(2 + i);
            indices.push_back(2 + ((i + 1) % segments));
        }
        
        self = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_id);
        self->AddComponent(Phoenix::SpriteComponent(Phoenix::SpriteType::Custom, "ressources/red-leader.jpg",  vertices, indices));
        self->AddComponent(Phoenix::TransformComponent{ {0, -10, -20}, 0, glm::vec3(1, 1, 1) });
        // self->SetRotation(-90, glm::vec3(1,0,0));
        self->BindUpdate(PX_BIND_EVENT_FN(Update));
        self->AddComponent(Phoenix::RigidBody(1, Phoenix::RigidbodyType::DYNAMIC));

}

void Centroid::Update()
{
    auto dt = Phoenix::Timer::GetDeltaTime();
    self->SetTransformPosition(self->GetTransformPosition() + m_Direction * m_Speed * dt);
    RotateBoidBasedOnDirection();
}

void Centroid::RotateBoidBasedOnDirection()
{
    if (glm::length(m_Direction) > 0.001f) {
        glm::vec3 defaultDirection = glm::vec3(0.0f, 1.0f, 0.f);
        
        glm::vec3 normalizedDirection = glm::normalize(m_Direction);
        
        glm::vec3 rotationAxis = glm::cross(defaultDirection, normalizedDirection);
        
        if (glm::length(rotationAxis) < 0.001f) {
            if (glm::dot(defaultDirection, normalizedDirection) < 0) {
                self->SetRotation(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            }
        } else {
            rotationAxis = glm::normalize(rotationAxis);
            
            float angle = acos(glm::dot(defaultDirection, normalizedDirection));
            float angleDegrees = angle * 180.0f / glm::pi<float>();
            
            self->SetRotation(angleDegrees, rotationAxis);
        }
    }
}
