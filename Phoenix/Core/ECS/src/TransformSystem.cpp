#include "ECS/include/TransformSystem.h"

#include <iostream>
#include "ECS/include/EntityManager.h"
#include "ECS/include/TransformsData.h"
#include "Log/include/Log.h"


namespace Phoenix
{
    void TransformSystem::InitComponents()
    {
    }

    void TransformSystem::StartComponents()
    {
    }

    void TransformSystem::UpdateComponents()
    {
    }

    void TransformSystem::DeleteComponentFrom(EntityId entity)
    {
        ComponentId transformId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        auto d = m_TransformsData->m_positions.begin();
        m_TransformsData->m_positions.Remove(transformId);
        m_TransformsData->m_rotations.Remove(transformId);
        m_TransformsData->m_scales.Remove(transformId);
        m_TransformsData->m_children.Remove(transformId);
        m_TransformsData->m_parents.Remove(transformId);
        ComponentSystem::DeleteComponentFrom(entity);
    }

    TransformSystem::TransformSystem(ComponentSystemId id, size_t dataSize)
        : ComponentSystem(id,dataSize)
    {
        m_TransformsData = new TransformsData(dataSize);
    }

    TransformSystem::~TransformSystem()
    {
        delete m_TransformsData;
        m_TransformsData = nullptr;
    }

    void TransformSystem::Init()
    {
        ComponentSystem::Init();
    }

    void TransformSystem::Start()
    {
        ComponentSystem::Start();
    }

    void TransformSystem::Update()
    {
        ComponentSystem::Update();
    }

    void TransformSystem::PrintEntityPosition(EntityId entity)
    {
        ComponentId transformId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        glm::vec2 position = m_TransformsData->m_positions.Get(transformId);
        PX_INFO("position : {0},{1}", position.x, position.y);
    }


    glm::vec3 TransformSystem::GetEntityPosition(EntityId entity)
    {
        ComponentId transformId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return glm::vec3(m_TransformsData->m_positions.Get(transformId));
    }

    float TransformSystem::GetEntityRotation(EntityId entity)
    {
        ComponentId transformId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_TransformsData->m_rotations.Get(transformId);
    }

    glm::vec2 TransformSystem::GetEntityScale(EntityId entity)
    {
        ComponentId transformId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_TransformsData->m_scales.Get(transformId);
    }

    void TransformSystem::SetEntityPostion(EntityId entity, glm::vec3 position)
    {
         ComponentId transformId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_TransformsData->m_positions.Get(transformId) = position;
    }

    void TransformSystem::SetEntityRotation(EntityId entity, float rotation)
    {
        ComponentId transformId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_TransformsData->m_rotations.Get(transformId) = rotation;
    }

    void TransformSystem::SetEntityScale(EntityId entity, glm::vec2 scale)
    {
        ComponentId transformId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_TransformsData->m_scales.Get(transformId) = scale;
    }
    
}
