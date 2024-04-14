#pragma once
#include <functional>
#include <map>
#include <vector>
#include <string>
#include "EntityComponent.h"
#include "Core/ECSExtended/include/Tag.h"

class ComponentSystem;

namespace Phoenix
{
    /**
     * @brief EntityManager class
     *         Base registry for all entities, used by the EntitySubsystem to create, remove and get entities
     * 
     */
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
        void BindOnStart(EntityId entityId, std::function<void()> onStartFunction);
        std::function<void()> GetUpdateFunction(EntityId entityId);
        void AddTag(EntityId entity, TagType tag);
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
        //So a ComponentSystem will access the componentId of an entity like this => EntityManager->m_entitiesComponents.at(EntityId).at(ComponentSystemId);
        std::vector<std::vector<ComponentId>> m_entitiesComponents;
    private:
        inline static EntityManager* m_instance = nullptr;
        std::vector<EntityId> m_entitiesId;
        std::vector<std::string> m_entitiesName;
        std::vector<TagType> m_entitiesTags;
        std::vector<bool> m_entitiesStandAlone;
        std::vector<std::function<void()>> m_updateFunctions;
      };
}
