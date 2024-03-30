#include "../include/AnimationSystem.h"

#include "ECS/include/EntityManager.h"


namespace Phoenix
{
    void AnimationSystem::InitComponents()
    {
    }

    void AnimationSystem::StartComponents()
    {
    }

    void AnimationSystem::UpdateComponents()
    {
    }

    void AnimationSystem::Init()
    {
    }

    void AnimationSystem::Start()
    {
    }

    void AnimationSystem::Update()
    {
    }

    AnimationSystem::AnimationSystem(ComponentSystemId id, size_t dataSize):
        ComponentSystem(id, dataSize)
    {
        m_AnimationData = new AnimationData(dataSize);
    }

    AnimationSystem::~AnimationSystem()
    {
    }

    void AnimationSystem::SetAnimationsEntityId(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_entitiesIds.Get(componentId) = entity;
    }
    
    bool AnimationSystem::HasAnimation(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_entitiesIds.Get(componentId) != -1;
    }

    std::vector<EntityId> AnimationSystem::GetEntitiesWithAnimation()
    {
        std::vector<EntityId> entities;
        for(auto entityId: m_AnimationData->m_entitiesIds)
        {
            if(entityId == -1) return entities;
            entities.push_back(entityId);
        }
        return entities;
    }

    void AnimationSystem::DeleteComponent(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_durations.Remove(componentId);
        m_AnimationData->m_currentTimes.Remove(componentId);
        m_AnimationData->m_currentFrames.Remove(componentId);
        m_AnimationData->m_totalFrames.Remove(componentId);
        m_AnimationData->m_names.Remove(componentId);
        m_AnimationData->m_texturesPaths.Remove(componentId);
        m_AnimationData->m_onAnimationEnd.Remove(componentId);
        m_AnimationData->m_entitiesIds.Get(componentId) = -1;
        m_AnimationData->m_currentAnimationNames.Remove(componentId);
        ComponentSystem::DeleteComponent(entity);
    }

    void AnimationSystem::SetCurrentAnimationName(EntityId entity, std::string name)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_currentAnimationNames.Get(componentId) = name;
    }
    

    std::string AnimationSystem::GetCurrentAnimationName(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_currentAnimationNames.Get(componentId);
    }
    
    void AnimationSystem::SetAnimationName(EntityId entity, std::string animationName)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        auto u = m_AnimationData->m_names.Get(componentId);
        m_AnimationData->m_names.Get(componentId).push_back(animationName);
    }

    std::vector<std::string> AnimationSystem::GetAnimationsNames(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_names.Get(componentId);
    }

    std::map<std::string, float> AnimationSystem::GetAnimationsDurations(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_durations.Get(componentId);
    }

    void AnimationSystem::SetAnimationDuration(EntityId entity, std::string animationName, float duration)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_durations.Get(componentId)[animationName] = duration;
    }

    float AnimationSystem::GetAnimationDuration(EntityId entity, std::string animationName)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_durations.Get(componentId)[animationName];
    }

    std::map<std::string, float> AnimationSystem::GetAnimationsCurrentTimes(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_currentTimes.Get(componentId);
    }

    std::map<std::string, int> AnimationSystem::GetAnimationsCurrentFrames(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_currentFrames.Get(componentId);
    }

    std::map<std::string, int> AnimationSystem::GetAnimationsTotalFrames(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_totalFrames.Get(componentId);
    }

    std::map<std::string, std::vector<std::string>> AnimationSystem::GetAnimationsTexturesPaths(EntityId entity)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_texturesPaths.Get(componentId);
    }

    void AnimationSystem::SetAnimationCurrentTime(EntityId entity, std::string animationName, float time)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_currentTimes.Get(componentId)[animationName] = time;
    }

    float AnimationSystem::GetAnimationCurrentTime(EntityId entity, std::string animationName)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_currentTimes.Get(componentId)[animationName];
    }
    
    int AnimationSystem::GetAnimationCurrentFrame(EntityId entity, std::string animationName)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_currentFrames.Get(componentId)[animationName];
    }
    
    void AnimationSystem::SetAnimationCurrentFrame(EntityId entity, std::string animationName, int frame)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_currentFrames.Get(componentId)[animationName] = frame;
    }

    int AnimationSystem::GetAnimationTotalFrames(EntityId entity, std::string animationName)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_totalFrames.Get(componentId)[animationName];
    }

    void AnimationSystem::SetAnimationTotalFrames(EntityId entity, std::string animationName, int totalFrames)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_totalFrames.Get(componentId)[animationName] = totalFrames;
    }

    void AnimationSystem::SetAnimationTexturesPaths(EntityId entity, std::string animationName, std::vector<std::string> texturesPaths)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_texturesPaths.Get(componentId)[animationName] = texturesPaths;
    }

    std::vector<std::string> AnimationSystem::GetAnimationTexturesPaths(EntityId entity, std::string animationName)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_texturesPaths.Get(componentId)[animationName];
    }

    void AnimationSystem::SetOnAnimationEnd(EntityId entity, std::string animationName, std::function<void()> onAnimationEnd)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        m_AnimationData->m_onAnimationEnd.Get(componentId)[animationName] = onAnimationEnd;
    }

    std::function<void()> AnimationSystem::GetOnAnimationEnd(EntityId entity, std::string animationName)
    {
        ComponentId componentId = EntityManager::Get()->m_entitiesComponents.at(entity).at(m_Id);
        return m_AnimationData->m_onAnimationEnd.Get(componentId)[animationName];
    }
}
