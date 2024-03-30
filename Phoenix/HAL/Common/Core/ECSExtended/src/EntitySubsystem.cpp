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

    void EntitySubsystem::DestroyEntity(EntityId id)
    {
        m_EntityManager->Remove(id);
    }

    Ref<Entity> EntitySubsystem::GetEntityByName(std::string name)
    {
        EntityId entityId  = m_EntityManager->GetEntityIdByName(name);
        TagType tag = m_EntityManager->GetTag(entityId);
        return CreateRef<Entity>(Entity{ entityId, name, tag });
    }

    Ref<Entity> EntitySubsystem::GetEntityById(EntityId id)
    {
        std::string name = m_EntityManager->GetEntityNameById(id);
        //If Entity not found return nullptr
        if (name == "") return nullptr;
        TagType tag = m_EntityManager->GetTag(id);
        return CreateRef<Entity>(Entity{ id, name, tag });
    }

    std::vector<Ref<Entity>> EntitySubsystem::GetEntities()
    {
        std::vector<Ref<Entity>> entities;
        for (auto& entityName : m_EntityManager->GetEntitiesName())
        {
            EntityId entityId = m_EntityManager->GetEntityIdByName(entityName);
            TagType tag = m_EntityManager->GetTag(entityId);
            std::function<void()> updateBindedFunction = m_EntityManager->GetUpdateFunction(entityId);
            Ref<Entity> entity = CreateRef<Entity>(Entity{ entityId, entityName });
            entity->m_Tag = tag;
            entity->m_updateFunction = updateBindedFunction;
            entities.push_back(entity);
        }
        return entities;
    }

    std::vector<Ref<Entity>> EntitySubsystem::GetEntitiesByTag(TagType tag)
    {
        std::vector<Ref<Entity>> entities;
        for (auto& entityName : m_EntityManager->GetEntitiesName())
        {
            EntityId entityId = m_EntityManager->GetEntityIdByName(entityName);
            TagType entityTag = m_EntityManager->GetTag(entityId);
            std::function<void()> updateBindedFunction = m_EntityManager->GetUpdateFunction(entityId);
            if (Tags::HasTag(entityTag, tag))
            {
                Ref<Entity> entity = CreateRef<Entity>(Entity{ entityId, entityName });
                entity->m_Tag = tag;
                entity->m_updateFunction = updateBindedFunction;
                entities.push_back(entity);
            }
        }
        return entities;
    }

    void EntitySubsystem::BindUpdate(EntityId entityId, std::function<void()> updateFunction)
    {
        m_EntityManager->BindUpdate(entityId, updateFunction);
    }


    void EntitySubsystem::AddTag(EntityId entity, TagType tag)
    {
        m_EntityManager->AddTag(entity, tag);
    }

    void EntitySubsystem::DeleteTag(EntityId entity, TagType tag)
    {
        m_EntityManager->AddTag(entity, tag);
    }

    TagType EntitySubsystem::GetTag(EntityId entity)
    {
        return m_EntityManager->GetTag(entity);
    }

    void EntitySubsystem::Update()
    {
        std::vector<Ref<Entity>> entities = GetEntities();
        for(auto& entity : entities)
        {
            entity->Update();
        }
    }
}
