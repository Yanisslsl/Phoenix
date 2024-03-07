#include "Windows/Core/Application/include/Application.h"

namespace Phoenix
{

    EntitySubsystem::EntitySubsystem()
    {
        m_EntityManager = new EntityManager();
        m_TransformSystem = new TransformSystem(0, 1000);
        // m_ColliderSystem = new ColliderSystem(1, 1000);
    }
    
    Ref<Entity> EntitySubsystem::CreateEntity(std::string name)
    {
        EntityId entityId = m_EntityManager->Create(name);
        return CreateRef<Entity>(Entity{ entityId,   name });
    }

    void EntitySubsystem::DestroyEntity(Entity entity)
    {
        m_EntityManager->Remove(entity.m_id);
    }

    Ref<Entity> EntitySubsystem::GetEntity(std::string name)
    {
        EntityId entityId  = m_EntityManager->GetEntity(name);
        return CreateRef<Entity>(Entity{ entityId, name });
    }

    std::vector<Ref<Entity>> EntitySubsystem::GetEntities()
    {
        std::vector<Ref<Entity>> entities;
        for (auto& entityName : m_EntityManager->GetEntitiesName())
        {
            auto entity = m_EntityManager->GetEntity(entityName);
            entities.push_back(CreateRef<Entity>(Entity{ entity, entityName }));
        }
        return entities;
    }
}
