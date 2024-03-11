
#include "ECS/include/ColliderSystem.h"

#include "Common/Core/Physics/include/CollisionSubSytem.h"
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
    
    void ColliderSystem::SetColliderPosition(EntityId entity, glm::vec2 position)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_positions.at(colliderId) = position;
    }

    void ColliderSystem::SetColliderHitCalls(EntityId entity, int hitCalls)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_hitCalls.at(colliderId) = hitCalls;
    }

    int ColliderSystem::GetColliderHitCalls(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_hitCalls.at(colliderId);
    }

    void ColliderSystem::SetColliderWidth(EntityId entity, float width)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_widths.at(colliderId) = width;
    }

    void ColliderSystem::SetColliderHeight(EntityId entity, float height)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_heights.at(colliderId) = height;
    }

    glm::vec2 ColliderSystem::GetColliderPosition(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_positions.at(colliderId);
    }

    float ColliderSystem::GetColliderWidth(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_widths.at(colliderId);
    }

    float ColliderSystem::GetColliderHeight(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_heights.at(colliderId);
    }

    void ColliderSystem::SetOnHitCallback(EntityId entity, std::function<void(Ref<Entity>)> callback)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_onHitCallbacks.at(colliderId) = callback;
    }
    
    std::function<void(Ref<Entity>)> ColliderSystem::GetOnHitCallback(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_onHitCallbacks.at(colliderId);
    }

    void ColliderSystem::SetColliderEntity(EntityId entity, EntityId colliderEntity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_entities.at(colliderId) = colliderEntity;
    }

    EntityId ColliderSystem::GetColliderEntity(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_entities.at(colliderId);
    }

    void ColliderSystem::SetColliderNodeId(EntityId entity, std::string nodeId)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_nodeIds.at(colliderId) = nodeId;
    }

    std::string ColliderSystem::GetColliderNodeId(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_nodeIds.at(colliderId);
    }
}
