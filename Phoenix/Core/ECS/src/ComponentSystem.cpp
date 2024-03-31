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
        // find the first item that is not consecutive
         const auto it = std::adjacent_find(begin(m_ComponentsId), end(m_ComponentsId),
         [](ComponentId lhs, ComponentId rhs){ return (lhs+1 != rhs); });
         if (it == end(m_ComponentsId))
         {
             m_ComponentsId.push_back(m_ComponentsId.size());
             EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id) = m_ComponentsId.back();
         }
         else
         {
             // if item is not consecutive, insert the new componentId at the position of the first item that is not consecutive
             const auto result = m_ComponentsId.insert(it+1, (*it)+1);
             EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id) = m_ComponentsId.at(*result);
         }
    }

    void ComponentSystem::DeleteComponentFrom(EntityId entity)
    {
        //@TODO: Refacto might be a order problem when deleting component and adding a new one, and maybe find other way to unset the componentId
        //Set the value as -1 so we know it's not use anymore
        EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id) = -1;
    }
}

