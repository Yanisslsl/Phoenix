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
        ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
        glm::vec2 position = m_TransformsData->m_positions.at(transformId);
        PX_INFO("position : {0},{1}", position.x, position.y);
    }


    glm::vec2 TransformSystem::GetEntityPosition(EntityId entity)
    {
        ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
        return m_TransformsData->m_positions.at(transformId);
    }

    float TransformSystem::GetEntityRotation(EntityId entity)
    {
        ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
        return m_TransformsData->m_rotations.at(transformId);
    }

    glm::vec2 TransformSystem::GetEntityScale(EntityId entity)
    {
        ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
        return m_TransformsData->m_scales.at(transformId);
    }

    void TransformSystem::SetEntityPostion(EntityId entity, glm::vec2 position)
    {
        ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
        m_TransformsData->m_positions.at(transformId) = position;
    }

    void TransformSystem::SetEntityRotation(EntityId entity, float rotation)
    {
        ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
        m_TransformsData->m_rotations.at(transformId) = rotation;
    }

    void TransformSystem::SetEntityScale(EntityId entity, glm::vec2 scale)
    {
        ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
        m_TransformsData->m_scales.at(transformId) = scale;
    }
    
}
