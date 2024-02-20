#include "ECS/include/ComponentSystem.h"
#include "ECS/include/EntityManager.h"

namespace Phoenix
{
    void ComponentSystem::Init()
    {
        InitComponents();
    }

    void ComponentSystem::Start()
    {
        StartComponents();
    }

    void ComponentSystem::Update()
    {
        UpdateComponents();
    }
    
    void ComponentSystem::AddComponentTo(EntityId entity)
    {
        //Ajouter à l'entityManager le componentId pour l'entité 
        const auto it = std::adjacent_find(begin(m_ComponentsId), end(m_ComponentsId),
        [](ComponentId lhs, ComponentId rhs){ return (lhs+1 != rhs); });
        if (it == end(m_ComponentsId))
        {
            m_ComponentsId.push_back(m_ComponentsId.size());
            auto len = EntityMgr.m_entitiesComponents;
            auto s = EntityMgr.m_entitiesComponents.at(entity);
            EntityMgr.m_entitiesComponents.at(entity).at(m_Id) = m_ComponentsId.back();
            //To Do : Call Init ?
        }
        else
        {
            const auto result = m_ComponentsId.insert(it+1, (*it)+1);
            EntityMgr.m_entitiesComponents.at(entity).at(m_Id) = m_ComponentsId.at(*result);
            //To Do : Call Init ?
        }
    }
}

