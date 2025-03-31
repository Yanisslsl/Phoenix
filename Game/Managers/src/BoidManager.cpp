#include "../include/BoidManager.h"

#include <iostream>

#include "../../Entities/include/Boid.h"
#include <random>
#include <glm/vec2.hpp>

#include "Core/Application/include/Application.h"
#include "Core/ECSExtended/include/TransformSubsytem.h"

BoidManager::BoidManager()
{
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("BoidManager");
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
    SpawnBoids();
    CreateBoundingBox();
}

void BoidManager::UpdateBoids()
{
    for(auto currentBoid: m_Boids)
    {
        glm::vec3 currentPos = currentBoid->GetManagedSelfEntity()->GetTransformPosition();
        glm::vec3 initialDirection = currentBoid->GetDirection();

        // init forces at each frame
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

            // if boid is too far, ignore it
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

        glm::vec3 avoidanceForce = currentBoid->GetAvoidanceVector();
        
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
             (avoidanceForce * m_avoidanceWeight) +
             (initialDirection * m_InertiaWeight)
         );
        } else {
            finalDirection = glm::normalize(
               (avoidanceForce * m_avoidanceWeight) +
               (initialDirection * m_InertiaWeight)
           );
        }
        
        currentBoid->SetDirection(finalDirection);
    }
}
void BoidManager::SpawnBoids()
{
    glm::vec3 minBounds(-m_cubeSize, -m_cubeSize, -m_cubeSize);
    glm::vec3 maxBounds(m_cubeSize, m_cubeSize, m_cubeSize);
    glm::vec3 dimensions = maxBounds - minBounds;

    int totalBoids = 800; 
    float spacing = 4.0f;

    float volume = dimensions.x * dimensions.y * dimensions.z;
    float boidDensity = totalBoids / volume;
    float averageDistance = std::pow(1.0f / boidDensity, 1.0f/3.0f);
    
    int numX = std::max(1, static_cast<int>((dimensions.x - 2 * spacing) / averageDistance));
    int numY = std::max(1, static_cast<int>((dimensions.y - 2 * spacing) / averageDistance));
    int numZ = std::max(1, static_cast<int>((dimensions.z - 2 * spacing) / averageDistance));
    
    while (numX * numY * numZ < totalBoids && (numX <= numY && numX <= numZ)) numX++;
    while (numX * numY * numZ < totalBoids && (numY <= numX && numY <= numZ)) numY++;
    while (numX * numY * numZ < totalBoids && (numZ <= numX && numZ <= numY)) numZ++;
    
    float stepX = numX > 1 ? (dimensions.x - 2 * spacing) / (numX - 1) : 0;
    float stepY = numY > 1 ? (dimensions.y - 2 * spacing) / (numY - 1) : 0;
    float stepZ = numZ > 1 ? (dimensions.z - 2 * spacing) / (numZ - 1) : 0;

    int boidCount = 0;
    for (int x = 0; x < numX && boidCount < totalBoids; x++) {
        for (int y = 0; y < numY && boidCount < totalBoids; y++) {
            for (int z = 0; z < numZ && boidCount < totalBoids; z++) {
                float posX = minBounds.x + spacing + x * stepX;
                float posY = minBounds.y + spacing + y * stepY;
                float posZ = minBounds.z + spacing + z * stepZ;
            
                float randOffset = 1.0f;
                posX += ((rand() % 100) / 100.0f - 0.5f) * randOffset;
                posY += ((rand() % 100) / 100.0f - 0.5f) * randOffset;
                posZ += ((rand() % 100) / 100.0f - 0.5f) * randOffset;
            
                std::string name = "Boid-" + std::to_string(boidCount);
                m_Boids.push_back(Phoenix::CreateRef<Boid>(
                    name, 
                    glm::vec3(posX, posY, posZ), 
                    glm::vec2(0, 0)
                ));
            
                boidCount++;
            }
        }
    }
}

void BoidManager::SetBoidSpeed(float speed)
{
    for(auto boid: m_Boids)
    {
        boid->SetSpeed(speed);
    }
    m_Speed = speed;
}

void BoidManager::CreateBoundingBox()
{
    glm::vec3 minBounds(-m_cubeSize, -m_cubeSize, -m_cubeSize);
    glm::vec3 maxBounds(m_cubeSize, m_cubeSize, m_cubeSize);
    glm::vec3 center = (minBounds + maxBounds) * 0.5f;
    glm::vec3 dimensions = maxBounds - minBounds;

    float wallThickness = 1.0f;

    auto leftWall = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("leftWall");
    leftWall->AddComponent(Phoenix::TransformComponent{ 
        {minBounds.x + wallThickness/2, center.y, center.z},
        0, 
        {wallThickness, dimensions.y, dimensions.z}
    });
    leftWall->AddComponent(Phoenix::RigidBody(0, Phoenix::RigidbodyType::STATIC, Phoenix::CollisionGroups::GROUP_ENEMY));

    auto rightWall = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("rightWall");
    rightWall->AddComponent(Phoenix::TransformComponent{ 
        {maxBounds.x - wallThickness/2, center.y, center.z}, 
        0, 
        {wallThickness, dimensions.y, dimensions.z}
    });
    rightWall->AddComponent(Phoenix::RigidBody(0, Phoenix::RigidbodyType::STATIC, Phoenix::CollisionGroups::GROUP_ENEMY));

    auto bottomWall = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("bottomWall");
    bottomWall->AddComponent(Phoenix::TransformComponent{ 
        {center.x, minBounds.y + wallThickness/2, center.z}, 
        0, 
        {dimensions.x, wallThickness, dimensions.z}
    });
    bottomWall->AddComponent(Phoenix::RigidBody(0, Phoenix::RigidbodyType::STATIC, Phoenix::CollisionGroups::GROUP_ENEMY));

    auto topWall = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("topWall");
    topWall->AddComponent(Phoenix::TransformComponent{ 
        {center.x, maxBounds.y - wallThickness/2, center.z}, 
        0, 
        {dimensions.x, wallThickness, dimensions.z}
    });
    topWall->AddComponent(Phoenix::RigidBody(0, Phoenix::RigidbodyType::STATIC, Phoenix::CollisionGroups::GROUP_ENEMY));

    auto backWall = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("backWall");
    backWall->AddComponent(Phoenix::TransformComponent{ 
        {center.x, center.y, minBounds.z + wallThickness/2}, 
        0, 
        {dimensions.x, dimensions.y, wallThickness}
    });
    backWall->AddComponent(Phoenix::RigidBody(0, Phoenix::RigidbodyType::STATIC, Phoenix::CollisionGroups::GROUP_ENEMY));

    auto frontWall = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("frontWall");
    frontWall->AddComponent(Phoenix::TransformComponent{ 
        {center.x, center.y, maxBounds.z - wallThickness/2}, 
        0, 
        {dimensions.x, dimensions.y, wallThickness}
    });
    frontWall->AddComponent(Phoenix::RigidBody(0, Phoenix::RigidbodyType::STATIC, Phoenix::CollisionGroups::GROUP_ENEMY));
}


void BoidManager::Update()
{
    UpdateBoids();
}

