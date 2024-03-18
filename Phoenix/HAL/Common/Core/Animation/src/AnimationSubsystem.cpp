#include "../include/AnimationSubsystem.h"

#include "Utils/Timer.h"
#include "Windows/Core/Application/include/Application.h"

namespace Phoenix
{
    AnimationSubsystem::AnimationSubsystem()
    {
        m_AnimationSystem = new AnimationSystem(2, 1000);
    }

    AnimationSubsystem::~AnimationSubsystem()
    {
        delete m_AnimationSystem;
    }

    // AnimatorComponent::AnimatorComponent(std::string name, int totalFrames, float duration, std::vector<std::string> paths)
    // {
    //     texturesPaths.insert(std::pair<std::string, std::vector<std::string>>(name, paths));
    // }

    AnimatorComponent AnimationSubsystem::GetAnimatorComponent(EntityId entity)
    {
        std::vector<std::string> names = m_AnimationSystem->GetAnimationsNames(entity);
        std::map<std::string, float> durations = m_AnimationSystem->GetAnimationsDurations(entity);
        std::map<std::string, float> currentTimes = m_AnimationSystem->GetAnimationsCurrentTimes(entity);
        std::map<std::string, int> currentFrames = m_AnimationSystem->GetAnimationsCurrentFrames(entity);
        std::map<std::string, int> totalFrames = m_AnimationSystem->GetAnimationsTotalFrames(entity);
        std::map<std::string, std::vector<std::string>> texturesPaths = m_AnimationSystem->GetAnimationsTexturesPaths(entity);
        auto currentAnimation = m_AnimationSystem->GetCurrentAnimationName(entity);
        AnimatorComponent animator = {currentAnimation, names, durations, currentTimes, currentFrames, totalFrames, texturesPaths};
        return animator;
    }

    void AnimationSubsystem::CreateAnimation(EntityId entity, std::string name, int totalFrames, float duration, std::vector<std::string> paths)
    {
        std::string entityName = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(entity)->m_name;
        if(!m_AnimationSystem->HasAnimation(entity))
        {
            m_AnimationSystem->AddComponentTo(entity);
        }
        m_AnimationSystem->SetAnimationDuration(entity, name , duration);
        m_AnimationSystem->SetAnimationName(entity, name);
        m_AnimationSystem->SetAnimationTotalFrames(entity, name , totalFrames);
        m_AnimationSystem->SetAnimationCurrentFrame(entity, name , 0);
        m_AnimationSystem->SetAnimationCurrentTime(entity, name , 0);
        m_AnimationSystem->SetAnimationTexturesPaths(entity, name , paths);
        m_AnimationSystem->SetAnimationsEntityId(entity);
        m_AnimationSystem->SetCurrentAnimationName(entity, "NONE");
        Renderer::SetTexturesPaths(entityName, name , paths);
    }

    void AnimationSubsystem::PlayAnimation(EntityId entity, std::string name, std::function<void()> onAnimationEnd)
    {
        auto animationsNames= m_AnimationSystem->GetAnimationsNames(entity);
        if(animationsNames.size() == 0)
        {
            PX_ERROR("No animations found for entity with id: {0}", entity);
            return;
        }
        if(std::find(animationsNames.begin(), animationsNames.end(), name) == animationsNames.end())
        {
            PX_ERROR("Animation with name: {0} not found for entity with id: {1}", name, entity);
            return;
        }
        m_AnimationSystem->SetCurrentAnimationName(entity, name);
        if(onAnimationEnd)
        {
            m_AnimationSystem->SetOnAnimationEnd(entity, name, onAnimationEnd);
        }
        std::string entityName = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(entity)->m_name;
        Renderer::EnableShapeTexture(entityName, name);
    }

    void AnimationSubsystem::Update()
    {
        std::vector<EntityId> entities = m_AnimationSystem->GetEntitiesWithAnimation();
        if(entities.size() == 0) return;
        for(auto entity : entities)
        {
            auto u = m_AnimationSystem->GetCurrentAnimationName(entity);
            if(m_AnimationSystem->GetCurrentAnimationName(entity) == "NONE") continue;
            UpdateAnimation(entity);
        }
    }

    void AnimationSubsystem::UpdateAnimation(EntityId entityId)
    {
        float deltaTime = Timer::GetDeltaTime();
        auto currentAnimation = m_AnimationSystem->GetCurrentAnimationName(entityId);
        auto totalFrames = m_AnimationSystem->GetAnimationTotalFrames(entityId, currentAnimation);
        float currentTime = m_AnimationSystem->GetAnimationCurrentTime(entityId, currentAnimation);
        auto duration = m_AnimationSystem->GetAnimationDuration(entityId, currentAnimation);
        auto currentFrame = m_AnimationSystem->GetAnimationCurrentFrame(entityId, currentAnimation);
        auto textures = m_AnimationSystem->GetAnimationTexturesPaths(entityId, currentAnimation);
        auto onAnimationEnd = m_AnimationSystem->GetOnAnimationEnd(entityId, currentAnimation);
        if(currentTime >= duration)
        {
            currentTime = 0;
            currentFrame++;
            if(currentFrame >= totalFrames)
            {
                currentFrame = 0;
                if(onAnimationEnd)
                {
                    onAnimationEnd();
                }
            }
            m_AnimationSystem->SetAnimationCurrentTime(entityId, currentAnimation, currentTime);
            std::string entityName = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(entityId)->m_name;
            m_AnimationSystem->SetAnimationCurrentFrame(entityId, currentAnimation, currentFrame);
            Renderer::SetTextureIndex(entityName, currentFrame);
        }
        else
        {
            currentTime += deltaTime;
            m_AnimationSystem->SetAnimationCurrentTime(entityId, currentAnimation, currentTime);
        }
    }
}
