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

    std::vector<EntityId> ColliderSystem::GetCollidersEntitiesIds()
    {
        std::vector<EntityId> entities;
        for (auto& entity : m_ColliderData->m_entities)
        {
            if(entity == -1) continue;
            entities.push_back(entity);
        }
        return entities;
    }

    ColliderSystem::~ColliderSystem()
    {
        
    }

    void ColliderSystem::DeleteComponent(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_types.Remove(componentId);
        m_ColliderData->m_positions.Remove(componentId);
        m_ColliderData->m_widths.Remove(componentId);
        m_ColliderData->m_heights.Remove(componentId);
        m_ColliderData->m_hitCalls.Remove(componentId);
        m_ColliderData->m_onHitCallbacks.Remove(componentId);
        m_ColliderData->m_entities.Remove(componentId, -1);
        m_ColliderData->m_nodeIds.Remove(componentId);
        m_ColliderData->m_shapes.Remove(componentId);
        ComponentSystem::DeleteComponent(entity);
    }

    bool ColliderSystem::HasCollider(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        if(componentId == -1) return false;
        return m_ColliderData->m_entities.Get(componentId) != -1;
    }

    ColliderSystem::ColliderSystem(ComponentSystemId id, size_t dataSize)
        : ComponentSystem(id, dataSize)
    {
        m_ColliderData = new ColliderData(dataSize);
    }

    CollisionType ColliderSystem::GetColliderType(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_types.Get(colliderId);
    }
    
    void ColliderSystem::SetColliderType(EntityId entity, CollisionType type)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_types.Get(colliderId) = type;
    }
    
    void ColliderSystem::SetColliderPosition(EntityId entity, glm::vec2 position)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_positions.Get(colliderId) = position;
    }

    void ColliderSystem::SetColliderHitCalls(EntityId entity, int hitCalls)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_hitCalls.Get(colliderId) = hitCalls;
    }

    int ColliderSystem::GetColliderHitCalls(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_hitCalls.Get(colliderId);
    }

    void ColliderSystem::SetColliderWidth(EntityId entity, float width)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_widths.Get(colliderId) = width;
    }

    void ColliderSystem::SetColliderHeight(EntityId entity, float height)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_heights.Get(colliderId) = height;
    }

    glm::vec2 ColliderSystem::GetColliderPosition(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_positions.Get(colliderId);
    }

    float ColliderSystem::GetColliderWidth(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        if(colliderId == -1) return 0;
        return m_ColliderData->m_widths.Get(colliderId);
    }

    float ColliderSystem::GetColliderHeight(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        if(colliderId == -1) return 0;
        return m_ColliderData->m_heights.Get(colliderId);
    }

    void ColliderSystem::SetOnHitCallback(EntityId entity, std::function<void(Ref<Entity>)> onHitCallback)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_onHitCallbacks.Get(colliderId) = onHitCallback;
    }
    
    std::function<void(Ref<Entity>)> ColliderSystem::GetOnHitCallback(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_onHitCallbacks.Get(colliderId);
    }

    void ColliderSystem::SetColliderEntity(EntityId entity, EntityId colliderEntity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_entities.Get(colliderId) = colliderEntity;
    }

    EntityId ColliderSystem::GetColliderEntity(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_entities.Get(colliderId);
    }

    void ColliderSystem::SetColliderNodeId(EntityId entity, std::string nodeId)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_ColliderData->m_nodeIds.Get(colliderId) = nodeId;
    }

    std::string ColliderSystem::GetColliderNodeId(EntityId entity)
    {
        ComponentId colliderId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_ColliderData->m_nodeIds.Get(colliderId);
    }
}
