#include "Windows/Core/Application/include/Application.h"

namespace Phoenix
{

    EntitySubsystem::EntitySubsystem()
    {
        m_EntityManager = new EntityManager();
    }

    EntitySubsystem::~EntitySubsystem()
    {
        delete m_EntityManager;
    }
    
    Ref<Entity> EntitySubsystem::CreateEntity(std::string name, bool isStandAlone)
    {
        EntityId entityId = m_EntityManager->Create(name);
        m_EntityManager->SetIsStandAlone(entityId, isStandAlone);
        return CreateRef<Entity>(Entity( entityId,   name, 0, isStandAlone ));
    }

    void EntitySubsystem::DestroyEntity(EntityId id)
    {
        m_EntityManager->Remove(id);
    }

    Ref<Entity> EntitySubsystem::GetEntityByName(std::string name)
    {
        EntityId entityId  = m_EntityManager->GetEntity(name);
        TagType tag = m_EntityManager->GetTag(entityId);
        bool isStandAlone = m_EntityManager->GetIsStandAlone(entityId);
        return CreateRef<Entity>(Entity{ entityId, name, tag, isStandAlone });
    }

    Ref<Entity> EntitySubsystem::GetEntityById(EntityId id)
    {
        //@TODO: ADD CATCHING ERROR
        std::string name = m_EntityManager->GetEntityName(id);
        TagType tag = m_EntityManager->GetTag(id);
        bool isStandAlone = m_EntityManager->GetIsStandAlone(id);
        return CreateRef<Entity>(Entity{ id, name, tag, isStandAlone });
    }

    std::vector<Ref<Entity>> EntitySubsystem::GetEntities()
    {
        std::vector<Ref<Entity>> entities;
        for (auto& entityName : m_EntityManager->GetEntitiesName())
        {
            EntityId entityId = m_EntityManager->GetEntity(entityName);
            TagType tag = m_EntityManager->GetTag(entityId);
            bool isStandAlone = m_EntityManager->GetIsStandAlone(entityId);
            std::function<void()> updateBindedFunction = m_EntityManager->GetUpdateFunction(entityId);
            Ref<Entity> entity = CreateRef<Entity>(Entity( entityId, entityName, tag, isStandAlone ));
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
            EntityId entityId = m_EntityManager->GetEntity(entityName);
            TagType entityTag = m_EntityManager->GetTag(entityId);
            bool isStandAlone = m_EntityManager->GetIsStandAlone(entityId);
            std::function<void()> updateBindedFunction = m_EntityManager->GetUpdateFunction(entityId);
            if (Tags::HasTag(entityTag, tag))
            {
                Ref<Entity> entity = CreateRef<Entity>(Entity{ entityId, entityName, tag, isStandAlone });
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
