#include "ECS/include/TransformSystem.h"

#include <iostream>

#include "ECS/include/EntityManager.h"
#include "ECS/include/TransformsData.h"

void Phoenix::TransformSystem::InitComponents()
{
}

void Phoenix::TransformSystem::StartComponents()
{
}

void Phoenix::TransformSystem::UpdateComponents()
{
}

Phoenix::TransformSystem::TransformSystem(ComponentSystemId id, size_t dataSize)
    : ComponentSystem(id,dataSize)
{
    m_TransformsData = new TransformsData(dataSize);
}

Phoenix::TransformSystem::~TransformSystem()
{
    delete m_TransformsData;
    m_TransformsData = nullptr;
}

void Phoenix::TransformSystem::Init()
{
    ComponentSystem::Init();
}

void Phoenix::TransformSystem::Start()
{
    ComponentSystem::Start();
}

void Phoenix::TransformSystem::Update()
{
    ComponentSystem::Update();
}

void Phoenix::TransformSystem::PrintEntityPosition(EntityId entity)
{
    ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
    glm::vec2 position = m_TransformsData->m_positions.at(transformId);
    std::cout<<"position : "<<position.x << ","<<position.y<<std::endl;
}

void Phoenix::TransformSystem::SetEntityPostion(EntityId entity, glm::vec2 position)
{
    ComponentId transformId = EntityMgr.m_entitiesComponents.at(entity).at(m_Id);
    m_TransformsData->m_positions.at(transformId) = position;
}
