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
         m_ComponentsId.push_back(m_ComponentsId.size());
             EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id) = m_ComponentsId.back();
    }

    void ComponentSystem::DeleteComponent(EntityId entity)
    {
       
    }
}

