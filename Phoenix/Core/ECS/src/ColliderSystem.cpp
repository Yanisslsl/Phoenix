
#include "ECS/include/ColliderSystem.h"

#include "ECS/include/EntityManager.h"

namespace Phoenix
{
    void ColliderSystem::InitComponents()
    {
    }

    void ColliderSystem::StartComponents()
    {
    }

    void ColliderSystem::UpdateComponents()
    {
    }

    void ColliderSystem::Init()
    {
    }

    void ColliderSystem::Start()
    {
    }

    void ColliderSystem::Update()
    {
    }

    ColliderSystem::~ColliderSystem()
    {
        
    }

    ColliderSystem::ColliderSystem(ComponentSystemId id, size_t dataSize)
        : ComponentSystem(id, dataSize)
    {
        m_ColliderData = new ColliderData(dataSize);
    }

    CollisionType ColliderSystem::GetColliderType(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_types.at(colliderId);
    }
    
    void ColliderSystem::SetColliderType(EntityId entity, CollisionType type)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_types.at(colliderId) = type;
    }
    
    void ColliderSystem::SetColliderCoordinates(EntityId entity, ColliderCoordinates coordinates)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_coordinates.at(colliderId) = coordinates;
    }
    
    ColliderCoordinates ColliderSystem::GetColliderCoordinates(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_coordinates.at(colliderId);
    }

    void ColliderSystem::SetOnHitCallback(EntityId entity, std::function<void(void*)> callback)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_onHitCallbacks.at(colliderId) = callback;
    }
    
    std::function<void(void*)> ColliderSystem::GetOnHitCallback(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_onHitCallbacks.at(colliderId);
    }
    
}
