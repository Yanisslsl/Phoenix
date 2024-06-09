
#include "Core/ECSExtended/include/EntitySubsystem.h"
#include <entt/entt.hpp>

#include "Core/Application/include/Application.h"

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

    void EntitySubsystem::Initalize()
    {
        OnStart();
    }

    Ref<Entity> EntitySubsystem::CreateEntity(std::string name, bool isStandAlone)
    {   
        entt::entity entity = Application::Get().GetRegistry().create();
        Application::Get().GetRegistry().emplace<EntityType>(entity, name, isStandAlone);
        return CreateRef<Entity>(Entity( entity,   name, 0, isStandAlone ));
    }

    void EntitySubsystem::DestroyEntity(EntityIdentifier entity)
    {
        Application::Get().GetRegistry().destroy(entity);
        auto view = Application::Get().GetRegistry().view<EntityType>();
        if(view.empty())
        {
            m_Binded_OnStarts.clear();
        }
    }

    Ref<Entity> EntitySubsystem::GetEntityByName(std::string name)
    {
        std::vector<Ref<Entity>> entities;
        auto view = Application::Get().GetRegistry().view<EntityType>();
        for(auto entity : view)
        {
            const auto _entity = view.get<EntityType>(entity);
            if(_entity.name == name)
            {
                return CreateRef<Entity>(entity, _entity.name, _entity.tag, _entity.isStandAlone);
            }
        }
        return nullptr;
    }

    Ref<Entity> EntitySubsystem::GetEntityById(EntityIdentifier id)
    {
        auto view = Application::Get().GetRegistry().view<EntityType>();
        for(auto entity : view)
        {
            const auto _entity = view.get<EntityType>(entity);
            if(entity == id)
            {
                return CreateRef<Entity>(entity, _entity.name, _entity.tag, _entity.isStandAlone);
            }
        }
        return nullptr;
    }

    std::vector<Ref<Entity>> EntitySubsystem::GetEntities()
    {
        std::vector<Ref<Entity>> entities;
        auto view = Application::Get().GetRegistry().view<EntityType>();
        for(auto entity : view)
        {
            const auto _entity = view.get<EntityType>(entity);
            entities.push_back(CreateRef<Entity>(entity, _entity.name, _entity.tag, _entity.isStandAlone));
        }
        return entities;
    }

    std::vector<Ref<Entity>> EntitySubsystem::GetEntitiesByTag(TagType tag)
    {
        std::vector<Ref<Entity>> entities;
        auto view = Application::Get().GetRegistry().view<EntityType>();
        for(auto entity : view)
        {
            const auto _entity = view.get<EntityType>(entity);
            if(Tags::HasTag(_entity.tag, tag))
            {
                entities.push_back(CreateRef<Entity>(entity, _entity.name, _entity.tag, _entity.isStandAlone));
            }
        }
        return entities;
    }

    void EntitySubsystem::SetIsInitialized(bool value)
    {
        if(value)
        {
            Initalize();
        }
        is_Initialized = value;
    }

    void EntitySubsystem::BindUpdate(EntityId entityId, std::function<void()> updateFunction)
    {
        m_EntityManager->BindUpdate(entityId, updateFunction);
    }
    
    void EntitySubsystem::BindOnStart(std::function<void()> onStartFunction)
    {
        m_Binded_OnStarts.push_back({false, onStartFunction});
    }

    void EntitySubsystem::AddTag(EntityIdentifier entity, TagType tag)
    {
        Application::Get().GetRegistry().patch<EntityType>(entity, [tag](EntityType& entity)
        {
            entity.tag = tag;
        });
    }

    void EntitySubsystem::DeleteTag(EntityIdentifier entity, TagType tag)
    {
        Application::Get().GetRegistry().patch<EntityType>(entity, [tag](EntityType& entity)
        {
            entity.tag = Tags::RemoveTag(entity.tag, tag);
        });
    }

    TagType EntitySubsystem::GetTag(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().get<EntityType>(entity).tag;
    }

    void EntitySubsystem::Update()
    {
        std::vector<Ref<Entity>> entities = GetEntities();
        for(auto& entity : entities)
        {
            entity->Update();
        }
    }

    void EntitySubsystem::OnStart()
    {
        for(auto& onStartFunction: m_Binded_OnStarts)
        {
            if(!onStartFunction.isCalled)
            {
                onStartFunction.onStartFunction();
                onStartFunction.isCalled = true;
            }
        }
    }
}
