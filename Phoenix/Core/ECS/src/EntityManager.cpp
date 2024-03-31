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
        m_entitiesComponents.resize(size);
        m_entitiesTags.resize(size);
        m_updateFunctions.resize(size);
        m_entitiesStandAlone.resize(size);
        for (std::vector<ComponentId>& c : m_entitiesComponents)
        {
            //@TODO: might be too restrictive, client should be able to add components without the need to edit the engine
            //@TODO: add method that allow to resize the vector when creating new ComponentSystem
            //Replace 5 by the number of ComponentSystem in the Engine
            c.resize(5,  -1);
        }
    }

    /// Creates a new entity and returns its ID
    /// so that IDs always are in ascending order
    /// Returns the ID of the created entity
    EntityId EntityManager::Create(const std::string& _name)
    {
         const auto it = std::adjacent_find(begin(m_entitiesId), end(m_entitiesId),
            [](EntityId lhs, EntityId rhs){ return (lhs+1 != rhs); });
        m_entitiesId.push_back(m_entitiesId.size());
        m_entitiesName.push_back(_name);
        return m_entitiesId.back();
    }

    void EntityManager::BindUpdate(EntityId entityId, std::function<void()> updateFunction)
    {
        m_updateFunctions.at(entityId) = std::move(updateFunction);
    }

    std::function<void()> EntityManager::GetUpdateFunction(EntityId entityId)
    {
        return m_updateFunctions.at(entityId);
    }
    
    void EntityManager::AddTag(EntityId entity, TagType tag)
    {
        m_entitiesTags.at(entity) = tag;
    }

    TagType EntityManager::GetTag(EntityId entity)
{
        return m_entitiesTags.at(entity);
    }

    void EntityManager::SetIsStandAlone(EntityId entity, bool isStandAlone)
    {
        m_entitiesStandAlone.at(entity) = isStandAlone;
    }

    bool EntityManager::GetIsStandAlone(EntityId entity)
    {
        return m_entitiesStandAlone.at(entity);
    }

    /// Remove an entity given its ID
    void EntityManager::Remove(EntityId entity)
    {
        const auto it = std::find(begin(m_entitiesId), end(m_entitiesId), entity);
        if (it != m_entitiesId.end() || (it == m_entitiesId.end() && *it == entity))
        {
            // m_entitiesName.at(m_entitiesName.begin() + std::distance(m_entitiesId.begin(),it));
            // find the index the entity name at the right index and set it to -1
            auto entityName = std::find(m_entitiesName.begin(), m_entitiesName.end(), m_entitiesName.at(std::distance(m_entitiesId.begin(),it)));
            m_entitiesName.at(std::distance(m_entitiesName.begin(),entityName)) = "";
            auto entityId = m_entitiesId.begin() + std::distance(m_entitiesId.begin(),it);
            m_entitiesId.at(std::distance(m_entitiesId.begin(),entityId)) = -1;
        }
        else
        {
        }
    }

    void EntityManager::PrintEntityName(EntityId entity)
    {
        std::cout<<m_entitiesName.at(entity)<<std::endl;
    }

    // retrieve entity and components
    EntityId EntityManager::GetEntityIdByName(const std::string& name)
    {
        for (std::size_t i = 0; i < m_entitiesName.size(); i++)
        {
            if (m_entitiesName.at(i) == name)
            {
                if(m_entitiesId.at(i) == -1) continue;
                return m_entitiesId.at(i);
            } 
        }
        return -1;
    }

    std::string EntityManager::GetEntityNameById(EntityId id)
    {
        if (id > m_entitiesName.size()-1)
        {
            PX_WARN("Entity with id:"+std::to_string(id)+" couldn't be found.");
            return "";
        }
        return m_entitiesName.at(id);
    }

    std::vector<EntityId> EntityManager::GetEntities() const
    {
        return m_entitiesId;
    }

    std::vector<std::string> EntityManager::GetEntitiesName() const
    {
        return m_entitiesName;
    }
}
