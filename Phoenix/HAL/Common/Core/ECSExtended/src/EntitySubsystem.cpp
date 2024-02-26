#include "../include/EntitySubsystem.h"

#include "Windows/Core/Application/include/Application.h"


namespace Phoenix
{

    EntitySubsystem::EntitySubsystem()
    {
        m_EntityManager = new EntityManager();
        m_TransformSystem = new TransformSystem(0, 1000);
    }
    
    Ref<Entity> EntitySubsystem::CreateEntity(std::string name)
    {
        EntityId entityId = m_EntityManager->Create(name);
        return CreateRef<Entity>(Entity{ this, entityId, name });
    }

    void EntitySubsystem::DestroyEntity(Entity entity)
    {
        m_EntityManager->Remove(entity.m_id);
    }

    Ref<Entity> EntitySubsystem::GetEntity(std::string name)
    {
        EntityId entityId  = m_EntityManager->GetEntity(name);
        return CreateRef<Entity>(Entity{ this, entityId, name });
    }

}
