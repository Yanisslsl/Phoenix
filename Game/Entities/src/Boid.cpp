#include "../include/Boid.h"

#include <iostream>
#include <glm/ext/scalar_constants.hpp>

#include "Core/Application/include/Application.h"
#include "Core/ECSExtended/include/TransformSubsytem.h"
#include "Utils/Timer.h"

Boid::Boid(std::string id, glm::vec3 position, glm::vec2 direction, int type)

{
    float height = 2.0f;
    int segments = 16;
    std::vector<float> vertices;
    std::vector<uint32_t> indices;

    float halfHeight = height / 2.0f;

    vertices.push_back(0.0f);          // x
    vertices.push_back(halfHeight);    // y
    vertices.push_back(0.0f);          // z
    vertices.push_back(0.5f);          // u
    vertices.push_back(0.0f);          // v

    vertices.push_back(0.0f);          // x
    vertices.push_back(-halfHeight);   // y
    vertices.push_back(0.0f);          // z
    vertices.push_back(0.5f);          // u
    vertices.push_back(1.0f);          // v

    for (int i = 0; i < segments; i++) {
        float M_PI = 3.14159265359f;
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments);
        float x = cos(angle);
        float z = sin(angle);
    
        vertices.push_back(x);                      // x
        vertices.push_back(-halfHeight);            // y
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
        
        m_id = id;
        self = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_id);
        self->AddComponent(Phoenix::SpriteComponent(Phoenix::SpriteType::Custom, "ressources/spaceship.jpg",  vertices, indices));
        self->AddComponent(Phoenix::TransformComponent{ {position.x, position.y, position.z}, 0, glm::vec3(1, 1, 1) });
        // self->SetRotation(-90, glm::vec3(1,0,0));
        self->AddComponent(Phoenix::RigidBody(1, Phoenix::RigidbodyType::STATIC, Phoenix::CollisionGroups::GROUP_PLAYER));
        self->BindUpdate(PX_BIND_EVENT_FN(Update));
}

void Boid::Update()
{
    auto dt = Phoenix::Timer::GetDeltaTime();
    self->SetTransformPosition(self->GetTransformPosition() + m_Direction * m_Speed * dt);
    RotateBoidBasedOnDirection();
    // DetectCollision();
}

void Boid::RotateBoidBasedOnDirection()
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

void Boid::DetectCollision()
{
    float radiusCercle = 5.0f;
    float goldenRatio = 1.61803398875f;
    float MAX_POINTS = 10;
    
    struct RaycastResult {
        glm::vec3 direction;
        bool hasHit;
    };
    std::vector<RaycastResult> results;
    
    auto frontHit = Phoenix::Application::Get().GetSubSystem<Phoenix::PhysicsSubsystem>()->TraceRayCast(
        self->GetTransformPosition(), 
        self->GetTransformPosition() + m_Direction * radiusCercle,
        Phoenix::CollisionGroups::GROUP_PLAYER, 
        Phoenix::CollisionGroups::GROUP_ENEMY,
        {
            0.1f,
            Phoenix::Color::RED,
            1.f
        }
    );
    
    if (!frontHit.hasHit) return;
    
    results.push_back({m_Direction, frontHit.hasHit});
    
    for(int i = 0; i <= (int)MAX_POINTS; i++)
    {
        float theta = glm::acos(1 - 2 * (i / MAX_POINTS));
        float phi = 360.f * goldenRatio * i;
        
        float x = glm::sin(theta) * glm::cos(phi);
        float y = glm::sin(theta) * glm::sin(phi);
        float z = glm::cos(theta);
        
        glm::vec3 rayDirection = glm::normalize(glm::vec3(x, y, z));
        glm::vec3 finalPosition = rayDirection * radiusCercle + self->GetTransformPosition();
        
        auto hit = Phoenix::Application::Get().GetSubSystem<Phoenix::PhysicsSubsystem>()->TraceRayCast(
            self->GetTransformPosition(), 
            finalPosition,
            Phoenix::CollisionGroups::GROUP_PLAYER, 
            Phoenix::CollisionGroups::GROUP_ENEMY,
            {
                0.1f,
                Phoenix::Color::RED,
                1.f
            }
        );
        
        results.push_back({rayDirection, hit.hasHit});
    }
    
    std::vector<glm::vec3> validDirections;
    for (const auto& result : results)
    {
        if (!result.hasHit)
        {
            validDirections.push_back(result.direction);
        }
    }
    
    if (validDirections.empty())
    {
        m_Direction = -m_Direction;
        return;
    }
    
    float bestDot = -1.0f;  // Worst dot possible
    glm::vec3 bestDirection;
    
    for (const auto& direction : validDirections)
    {
        float dotProduct = glm::dot(m_Direction, direction);
        
        if (dotProduct > bestDot)
        {
            bestDot = dotProduct;
            bestDirection = direction;
        }
    }
    
    m_Direction = bestDirection;
}