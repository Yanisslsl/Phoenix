#include "../include/EntitySubsystem.h"

#include "Windows/Core/Application/include/Application.h"


namespace Phoenix
{

    EntitySubsystem::EntitySubsystem()
    {
        m_EntityManager = new EntityManager();
        m_TransformSystem = new TransformSystem(0, 1000);
    }
    
    Entity* EntitySubsystem::CreateEntity(std::string name)
    {
        EntityId entityId = m_EntityManager->Create(name);
        return new Entity{ this, entityId, name };
    }

    void EntitySubsystem::DestroyEntity(Entity entity)
    {
        m_EntityManager->Remove(entity.m_id);
    }

}
