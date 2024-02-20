#include "ECS/include/EntityManager.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

#include "Log/include/Log.h"

namespace Phoenix
{
    EntityManager::EntityManager(size_t size)
    {
        m_entitiesId.reserve(size);
        m_entitiesName.reserve(size);
        m_entitiesComponents.resize(size, {});
        for (std::vector<ComponentId>& c : m_entitiesComponents)
        {
            //Replace 3 by the number of ComponentSystem in the Engine
            c.resize(3);
        }
    }

    /// Creates a new entity and returns its ID
    /// so that IDs always are in ascending order
    /// Returns the ID of the created entity
    EntityId EntityManager::Create(const std::string& _name)
    {
        const auto it = std::adjacent_find(begin(m_entitiesId), end(m_entitiesId),
            [](EntityId lhs, EntityId rhs){ return (lhs+1 != rhs); });
        if (it == end(m_entitiesId))
        {
            m_entitiesId.push_back(m_entitiesId.size());
            m_entitiesName.push_back(_name);
            return m_entitiesId.back();
        }
        else
        {
            const auto result = m_entitiesId.insert(it+1, (*it)+1);
            m_entitiesName.insert(
                m_entitiesName.begin() + std::distance(m_entitiesId.begin(),it) + 1,
                _name
            );
            return m_entitiesId.at((*result));
        }
    }

    /// Remove an entity given its ID
    void EntityManager::Remove(EntityId entity)
    {
        const auto it = std::find(begin(m_entitiesId), end(m_entitiesId), entity);
        if (it != m_entitiesId.end() || (it == m_entitiesId.end() && *it == entity))
        {
            m_entitiesName.erase(m_entitiesName.begin() + std::distance(m_entitiesId.begin(),it));
            m_entitiesId.erase(it);
        }
        else
        {
            PX_ERROR("Entity not found");
        }
    }

    void EntityManager::PrintEntityName(EntityId entity)
    {
        std::cout<<m_entitiesName.at(entity)<<std::endl;
    }

    void EntityManager::AddComponent(EntityId Entity, ComponentSystemId ComponentSystem, ComponentId Component)
    {
        m_entitiesComponents.at(Entity).at(ComponentSystem) = Component;
    }
}
