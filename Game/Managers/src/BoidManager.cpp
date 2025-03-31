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
    // Définir les limites du cube
    glm::vec3 minBounds(-25.0f, -25.0f, -25.0f);
    glm::vec3 maxBounds(25.0f, 25.0f, 25.0f);
    float boundaryMargin = 2.0f; // Marge à l'intérieur des limites
    float lookAheadDistance = 5.0f; // Distance de détection d'obstacles

    for(auto currentBoid: m_Boids)
    {
        glm::vec3 currentPos = currentBoid->GetManagedSelfEntity()->GetTransformPosition();
        glm::vec3 initialDirection = currentBoid->GetDirection();
        
        // Forces standard des boids
        glm::vec3 separationForce = glm::vec3(0.0f);
        glm::vec3 alignmentForce = glm::vec3(0.0f);
        glm::vec3 cohesionForce = glm::vec3(0.0f);
        glm::vec3 centerOfMass = glm::vec3(0.0f);
        int neighborCount = 0;
        
        // Force d'évitement des obstacles et des limites
        glm::vec3 avoidanceForce = glm::vec3(0.0f);
        bool needAvoidance = false;
        
        // === DÉTECTION D'OBSTACLES ===
        // Raycast frontal pour détecter des obstacles
        auto frontHit = Phoenix::Application::Get().GetSubSystem<Phoenix::PhysicsSubsystem>()->TraceRayCast(
            currentPos, 
            currentPos + initialDirection * lookAheadDistance,
            Phoenix::CollisionGroups::GROUP_PLAYER, 
            Phoenix::CollisionGroups::GROUP_ENEMY
        );
        
        if(frontHit.hasHit) {
            // Obstacle détecté, calculer direction d'évitement
            needAvoidance = true;
            
            // Effectuer des raycasts supplémentaires pour trouver une direction libre
            float goldenRatio = 1.61803398875f;
            float MAX_POINTS = 8;
            glm::vec3 bestDirection = initialDirection;
            float bestScore = -1.0f;
            
            for(int i = 0; i <= (int)MAX_POINTS; i++) {
                float theta = glm::acos(1 - 2 * (i / MAX_POINTS));
                float phi = 360.f * goldenRatio * i;
                
                float x = glm::sin(theta) * glm::cos(phi);
                float y = glm::sin(theta) * glm::sin(phi);
                float z = glm::cos(theta);
                
                glm::vec3 testDirection = glm::normalize(glm::vec3(x, y, z));
                
                // Évaluer cette direction
                // auto hit = Phoenix::Application::Get().GetSubSystem<Phoenix::PhysicsSubsystem>()->TraceRayCast(
                //     currentPos, 
                //     currentPos + testDirection * lookAheadDistance,
                //     Phoenix::CollisionGroups::GROUP_PLAYER, 
                //     Phoenix::CollisionGroups::GROUP_ENEMY,
                //     {
                //         0.1f,
                //         Phoenix::Color::YELLOW,
                //         0.5f
                //     }
                // );

                auto hit = Phoenix::Application::Get().GetSubSystem<Phoenix::PhysicsSubsystem>()->TraceRayCast(
                       currentPos, 
                       currentPos + testDirection * lookAheadDistance,
                       Phoenix::CollisionGroups::GROUP_PLAYER, 
                       Phoenix::CollisionGroups::GROUP_ENEMY
                );
                
                if(!hit.hasHit) {
                    // Direction libre, évaluer sa similarité avec la direction actuelle
                    float similarity = glm::dot(initialDirection, testDirection);
                    if(similarity > bestScore) {
                        bestScore = similarity;
                        bestDirection = testDirection;
                    }
                }
            }
            
            if(bestScore > -1.0f) {
                // Direction libre trouvée
                avoidanceForce = bestDirection;
            } else {
                // Aucune direction libre, inverser la direction
                avoidanceForce = -initialDirection;
            }
        }
        
        // === VÉRIFICATION DES LIMITES DU CUBE ===
        glm::vec3 boundaryAvoidance = glm::vec3(0.0f);
        bool nearBoundary = false;
        
        // Vérifier chaque dimension pour les limites
        if(currentPos.x < minBounds.x + boundaryMargin) {
            nearBoundary = true;
            boundaryAvoidance.x += 1.0f;
        }
        else if(currentPos.x > maxBounds.x - boundaryMargin) {
            nearBoundary = true;
            boundaryAvoidance.x -= 1.0f;
        }
        
        if(currentPos.y < minBounds.y + boundaryMargin) {
            nearBoundary = true;
            boundaryAvoidance.y += 1.0f;
        }
        else if(currentPos.y > maxBounds.y - boundaryMargin) {
            nearBoundary = true;
            boundaryAvoidance.y -= 1.0f;
        }
        
        if(currentPos.z < minBounds.z + boundaryMargin) {
            nearBoundary = true;
            boundaryAvoidance.z += 1.0f;
        }
        else if(currentPos.z > maxBounds.z - boundaryMargin) {
            nearBoundary = true;
            boundaryAvoidance.z -= 1.0f;
        }
        
        if(nearBoundary) {
            boundaryAvoidance = glm::normalize(boundaryAvoidance);
            // Combiner avec l'évitement d'obstacles si nécessaire
            if(needAvoidance) {
                avoidanceForce = glm::normalize(avoidanceForce + boundaryAvoidance);
            } else {
                avoidanceForce = boundaryAvoidance;
                needAvoidance = true;
            }
        }
        
        // === CALCUL DES FORCES STANDARD DES BOIDS ===
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
        
        // === COMBINAISON DE TOUTES LES FORCES ===
        glm::vec3 finalDirection;
        
        if(neighborCount > 0) {
            if(glm::length(separationForce) > 0.001f) {
                separationForce = glm::normalize(separationForce);
            }
            
            alignmentForce = glm::normalize(alignmentForce);
            
            centerOfMass /= static_cast<float>(neighborCount);
            cohesionForce = glm::normalize(centerOfMass - currentPos);
            
            if(needAvoidance) {
                // Ajouter la force d'évitement avec un poids élevé
                finalDirection = glm::normalize(
                    (separationForce * m_SeparationWeight) +
                    (cohesionForce * m_CohesionWeight) +
                    (alignmentForce * m_AlignmentWeight) +
                    (avoidanceForce * 2.5f) +  // Poids plus élevé pour l'évitement
                    (initialDirection * m_InertiaWeight)
                );
            } else {
                // Comportement standard sans évitement
                finalDirection = glm::normalize(
                    (separationForce * m_SeparationWeight) +
                    (cohesionForce * m_CohesionWeight) +
                    (alignmentForce * m_AlignmentWeight) +
                    (initialDirection * m_InertiaWeight)
                );
            }
        } else {
            // Sans voisins
            if(needAvoidance) {
                finalDirection = glm::normalize(avoidanceForce * 0.8f + initialDirection * 0.2f);
            } else {
                finalDirection = initialDirection;
            }
        }
        
        currentBoid->SetDirection(finalDirection);
    }
}
void BoidManager::Test()
{
    float M_PI = 3.14159265358979323846;
    for( int i = 0; i < 360; i += 5)
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

void BoidManager::CreateBoundingBox()
{
 
        // Taille du cube
        // glm::vec3 minBounds(-25.0f, -25.0f, -25.0f);
        // glm::vec3 maxBounds(25.0f, 25.0f, 25.0f);
        // glm::vec3 center = (minBounds + maxBounds) * 0.5f;
        // glm::vec3 dimensions = maxBounds - minBounds;
        //
        // // Créer une entité pour le cube
        // m_BoundingBox = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("BoundingBox");
        // m_BoundingBox->AddComponent(Phoenix::SpriteComponent("ressources/laser_beam.png", Phoenix::SpriteType::Cube));
        //
        // // Ajouter une composante de transformation
        // m_BoundingBox->AddComponent(Phoenix::TransformComponent{center, 0, dimensions});
        //
        // // Ajouter un corps rigide statique en mode trigger
        // m_BoundingBox->AddComponent(Phoenix::RigidBody(0, Phoenix::RigidbodyType::STATIC, Phoenix::CollisionGroups::GROUP_ENEMY));
        //
        // // Configurez le RigidBody pour qu'il soit creux (seulement les faces du cube)
        // // Cela dépend de votre API Bullet, mais généralement:
        // auto rigidBody = boundingBox->GetComponent<Phoenix::RigidBody>();
        // rigidBody->SetCollisionGroup(Phoenix::CollisionGroups::GROUP_BOUNDARY);
        // rigidBody->SetAsHollowBox(); // Vous devrez implémenter cette fonction
        //
        // m_BoundingBox = boundingBox;
}


void BoidManager::Update()
{
    UpdateBoids();
    // FollowCentroid();
}

