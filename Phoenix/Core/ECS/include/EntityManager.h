#pragma once
#include <map>
#include <vector>
#include <string>

#include "EntityComponent.h"
#include "../../../Core/Core.h"

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
        EntityId GetEntity(const std::string& name);
        std::vector<EntityId> GetEntities() const;
        std::vector<std::string> GetEntitiesName() const;
        static EntityManager* Get() { return new EntityManager();};
        //The ComponentId for each entity ordered by ComponentSystemId
        std::vector<std::vector<ComponentId>> m_entitiesComponents; //So a ComponentSystem will access the componentId of an entity like this => EntityManager->m_entitiesComponents.at(EntityId).at(ComponentSystemId);
    protected:
        void AddComponent(EntityId Entity, ComponentSystemId ComponentSystem, ComponentId Component);
        
    private:
        std::vector<EntityId> m_entitiesId;
        std::vector<std::string> m_entitiesName;
      };
}
