#include "../include/BoidManager.h"

#include <iostream>

#include "../../Entities/include/Boid.h"
#include <random>
#include <glm/vec2.hpp>

#include "Core/Application/include/Application.h"
#include "Utils/Timer.h"
#include "Core/ECSExtended/include/TransformSubsytem.h"

BoidManager::BoidManager()
{
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("BoidManager");
    // m_Centroid = Phoenix::CreateRef<Centroid>();
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
    Test();
}

void BoidManager::UpdateBoids()
{
    for(auto currentBoid: m_Boids)
    {
        glm::vec3 currentPos = currentBoid->GetManagedSelfEntity()->GetTransformPosition();
        glm::vec3 initialDirection = currentBoid->GetDirection();
        
        glm::vec3 separationForce = glm::vec3(0.0f);
        glm::vec3 alignmentForce = glm::vec3(0.0f);
        glm::vec3 cohesionForce = glm::vec3(0.0f);
        glm::vec3 centerOfMass = glm::vec3(0.0f);
        int neighborCount = 0;
        
        for(auto otherBoid: m_Boids)
        {
            if(currentBoid == otherBoid) continue;
            
            glm::vec3 otherPos = otherBoid->GetManagedSelfEntity()->GetTransformPosition();
            float distance = glm::distance(currentPos, otherPos);
            
            if(distance > maxDistance) continue;
            
            glm::vec3 awayVector = currentPos - otherPos;
            
            if(glm::length(awayVector) > 0.001f) {
                float ratio = 1.0f - (distance / maxDistance);
                if(ratio <= 0.0f) ratio = 0.1f;
                ratio = ratio * ratio;
                separationForce += glm::normalize(awayVector) * ratio;
                
                alignmentForce += otherBoid->GetDirection();
                
                centerOfMass += otherPos;
                
                neighborCount++;
            }
        }
        
        glm::vec3 finalDirection;
        
        if(neighborCount > 0) {
            if(glm::length(separationForce) > 0.001f) {
                separationForce = glm::normalize(separationForce);
            }
            
            alignmentForce = glm::normalize(alignmentForce);
            
            centerOfMass /= static_cast<float>(neighborCount);
            cohesionForce = glm::normalize(centerOfMass - currentPos);
            
            finalDirection = glm::normalize(
                (separationForce * m_SeparationWeight) +
                (cohesionForce * m_CohesionWeight) +
                (alignmentForce * m_AlignmentWeight) +
                (initialDirection * m_InertiaWeight)
            );
        } else {
            finalDirection = initialDirection;
        }
        
        currentBoid->SetDirection(finalDirection);
    }
}

void BoidManager::Test()
{
    float M_PI = 3.14159265358979323846;
    for( int i = 0; i < 360; i += 10)
    {
        std::string name = "Boid" + std::to_string(i);
        float x = cos(i * M_PI / 180) * 10;
        float z = sin(i * M_PI / 180) * 10;
        m_Boids.push_back(Phoenix::CreateRef<Boid>(name, glm::vec3(x, -10, z - 20), glm::vec2(0, 0)));
    }
    // for( int i = 0; i < 5; i ++)
    // {
    //     std::string name = "Boid" + std::to_string(i);
    //     m_Boids.push_back(Phoenix::CreateRef<Boid>(name, glm::vec3(i - 5, -10, 0), glm::vec2(0, 0)));
    // }
}

void BoidManager::SetCentroidSpeed(float speed)
{
    m_Centroid->SetSpeed(speed);
    for(auto boid: m_Boids)
    {
        boid->SetSpeed(speed);
    }
}

void BoidManager::FollowCentroid()
{
    auto dt = Phoenix::Timer::GetDeltaTime();
    auto cameraPos = Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera().GetPosition();
    auto direction = m_Centroid->GetManagedSelfEntity()->GetTransformPosition() - cameraPos;
    Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->LookAt(cameraPos + direction * m_Centroid->GetSpeed() * dt * 1.f);
    Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(cameraPos + glm::vec3(0,0,-1) * m_Centroid->GetSpeed() * dt * 1.f);
}


void BoidManager::Update()
{
    UpdateBoids();
    // FollowCentroid();
}

