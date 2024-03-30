#pragma once
#include <functional>
#include <map>
#include <vector>
#include <string>

#include "EntityComponent.h"
#include "../../../Core/Core.h"
#include "Common/Core/ECSExtended/include/Tag.h"

class ComponentSystem;

namespace Phoenix
{
    class PHOENIX_API EntityManager
    {
        friend ComponentSystem;
    public:
        EntityManager(size_t size = 1000);
        void Remove(EntityId entity);
        void PrintEntityName(EntityId);
        EntityId Create(const std::string& name);
        EntityId GetEntityIdByName(const std::string& name);
        std::string GetEntityNameById(EntityId id);
        std::vector<EntityId> GetEntities() const;
        std::vector<std::string> GetEntitiesName() const;
        void BindUpdate(EntityId entityId, std::function<void()> updateFunction);
        std::function<void()> GetUpdateFunction(EntityId entityId);
        void AddTag(EntityId entity, TagType tag);
        TagType GetTag(EntityId entity);
        static EntityManager* Get()
        {
            if(m_instance == nullptr)
            {
                m_instance = new EntityManager();
            }
            return m_instance;
        }
        //The ComponentId for each entity ordered by ComponentSystemId
        std::vector<std::vector<ComponentId>> m_entitiesComponents; //So a ComponentSystem will access the componentId of an entity like this => EntityManager->m_entitiesComponents.at(EntityId).at(ComponentSystemId);
    private:
        inline static EntityManager* m_instance = nullptr;
        std::vector<EntityId> m_entitiesId;
        std::vector<std::string> m_entitiesName;
        std::vector<TagType> m_entitiesTags;
        std::vector<std::function<void()>> m_updateFunctions;
      };
}
