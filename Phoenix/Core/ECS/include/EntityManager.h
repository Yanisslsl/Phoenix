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
        /**
         * Create an entity manager with the max number of entity it can hold
         */
        EntityManager(size_t size = 1000);
        /**
         * Remove the passed entity from the manager
         */
        void Remove(EntityId entity);
        /**
         * Print the name of the passed entity
         */
        void PrintEntityName(EntityId);
        /**
         * Create a new entity by passing it's name
         */
        EntityId Create(const std::string& name);
        /**
         * Get an entity id by it's name
         */
        EntityId GetEntityIdByName(const std::string& name);
        /**
         * Get an entity name by it's Id
         */
        std::string GetEntityNameById(EntityId id);
        /**
         * Get all entities
         */
        std::vector<EntityId> GetEntities() const;
        /**
         * Get all entities name
         */
        std::vector<std::string> GetEntitiesName() const;
        /**
         * Method to bind game update method to backend update
         */
        void BindUpdate(EntityId entityId, std::function<void()> updateFunction);
        void BindOnStart(EntityId entityId, std::function<void()> onStartFunction);
        /**
         * Get the binded game method
         */
        std::function<void()> GetUpdateFunction(EntityId entityId);
        /**
         * Add tag to the entity
         */
        void AddTag(EntityId entity, TagType tag);
        /**
         * Get entity tag
         */
        TagType GetTag(EntityId entity);
        void SetIsStandAlone(EntityId entity, bool isStandAlone);
        bool GetIsStandAlone(EntityId entity);
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
        std::vector<bool> m_entitiesStandAlone;
        std::vector<std::function<void()>> m_updateFunctions;
      };
}
