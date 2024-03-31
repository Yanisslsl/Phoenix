#include "ECS/include/SpriteSystem.h"
#include "ECS/include/EntityManager.h"
namespace Phoenix
{
    SpriteSystem::SpriteSystem(ComponentSystemId id, size_t dataSize):
        ComponentSystem(id, dataSize)
    {
        m_SpriteData = new SpriteData(dataSize);
    }

    SpriteSystem::~SpriteSystem()
    {
        delete m_SpriteData;
    }

    void SpriteSystem::InitComponents()
    {
    }

    void SpriteSystem::StartComponents()
    {
    }

    void SpriteSystem::UpdateComponents()
    {
    }

    void SpriteSystem::Init()
    {
    }

    void SpriteSystem::Start()
    {
    }

    void SpriteSystem::Update()
    {
    }

    void SpriteSystem::SetEntityId(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_SpriteData->m_entityIds.Get(componentId) = entity;
    }

    EntityId SpriteSystem::GetEntityId(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_SpriteData->m_entityIds.Get(componentId);
    }

    bool SpriteSystem::HasSprite(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_SpriteData->m_entityIds.Get(componentId) == entity;
    }

    void SpriteSystem::SetTexturePath(EntityId entity, std::string path)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_SpriteData->m_spritePaths.Get(componentId) = path;
    }

    std::string SpriteSystem::GetTexturePath(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_SpriteData->m_spritePaths.Get(componentId);
    }

    void SpriteSystem::SetColor(EntityId entity, ColorCode color)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_SpriteData->m_colors.Get(componentId) = color;
    }

    ColorCode SpriteSystem::GetColor(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_SpriteData->m_colors.Get(componentId);
    }
}
