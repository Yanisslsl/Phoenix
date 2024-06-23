#include "Core/Animation/include/AnimationSubsystem.h"
#include "Core/Application/include/Application.h"
#include "Core/ECSExtended/include/Entity.h"
#include "Core/ECSExtended/include/EntitySubsystem.h"
#include "Utils/Timer.h"

namespace Phoenix
{
    AnimationSubsystem::AnimationSubsystem()
    {
    }

    AnimationSubsystem::~AnimationSubsystem()
    {
    }

    bool AnimationSubsystem::HasAnimation(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().try_get<AnimatorComponent>(entity) != nullptr;
    }

    AnimatorComponent AnimationSubsystem::GetAnimatorComponent(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().get<AnimatorComponent>(entity);
    }

    void AnimationSubsystem::CreateAnimation(EntityIdentifier entity, std::string name, int totalFrames, float duration, std::vector<std::string> paths)
    {
        auto entityName = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(entity)->m_name;
        if(!HasAnimation(entity))
        {
            AnimatorComponent animator = AnimatorComponent();
            animator.currentAnimation = name;
            animator.durations =  std::map<std::string, float>({ {name, duration} });
            animator.texturesPaths = std::map<std::string, std::vector<std::string>>({ {name, paths} });
            animator.totalFrames = std::map<std::string, int>({ {name, totalFrames} });
            animator.names = std::vector<std::string>({ name });
            animator.currentTimes = std::map<std::string, float>();
            animator.currentTimes[name] = 0;
            animator.currentFrames = std::map<std::string, int>({ {name, 0} });
            Application::Get().GetRegistry().emplace<AnimatorComponent>(entity, animator);
            return;
        }
        
        auto view = Application::Get().GetRegistry().view<AnimatorComponent>();
        auto animator = view.get<AnimatorComponent>(entity);
        
        if(std::find(animator.names.begin(), animator.names.end(), name) != animator.names.end())
        {
            PX_ERROR("Animation name already exists for entity with id: {1}", name);
            return;
        }

        Application::Get().GetRegistry().patch<AnimatorComponent>(entity, [&name, &totalFrames, &duration, &paths](AnimatorComponent& component) 
        { 
            component.names.push_back(name);
            component.durations[name] = duration;
            component.texturesPaths[name] = paths;
            component.totalFrames[name] = totalFrames;
            component.currentTimes[name] = 0;
            component.currentFrames[name] = 0;
        });
        Application::Get().GetRenderer()->SetTexturesPaths(entityName, name , paths);
    }

    void AnimationSubsystem::PlayAnimation(EntityIdentifier entityId, std::string name, std::function<void()> onAnimationEnd)
    {
        if(!HasAnimation(entityId)) return;
        auto animatorComponent = GetAnimatorComponent(entityId);
        auto entity = Application::Get().GetRegistry().get<EntityType>(entityId);

        if(!animatorComponent.IsValid())
        {
            PX_ERROR("Animator component is not valid for entity with name: {0}", entity.name);
        }
     
        if(std::find(animatorComponent.names.begin(), animatorComponent.names.end(), name) == animatorComponent.names.end())
        {
            PX_ERROR("Animation with name: {0} not found for entity with name: {1}", name, entity.name);
            return;
        }

        Application::Get().GetRegistry().patch<AnimatorComponent>(entityId, [&name](AnimatorComponent& component) 
        { 
            component.currentAnimation = name;
        });
        
        if(onAnimationEnd)
        {
            Application::Get().GetRegistry().patch<AnimatorComponent>(entityId, [&](AnimatorComponent& component) 
            { 
                component.onAnimationEnds[name] = onAnimationEnd;
            });
        }
        
        Application::Get().GetRenderer()->EnableShapeTexture(entity.name, name);
    }

    void AnimationSubsystem::Update()
    {
        auto view = Application::Get().GetRegistry().view<AnimatorComponent>();
        for(auto entity : view)
        {
            auto animator = view.get<AnimatorComponent>(entity);
            if(animator.currentAnimation == "NONE") continue;
            UpdateAnimation(entity);
        }
    }

    void AnimationSubsystem::DeleteAnimation(EntityIdentifier entityId)
    {
        if(!HasAnimation(entityId)) return;
        Application::Get().GetRegistry().remove<AnimatorComponent>(entityId);
    }

    void AnimationSubsystem::UpdateAnimation(EntityIdentifier entityId)
    {
        float deltaTime = Timer::GetDeltaTime();
        auto animatorComponent = GetAnimatorComponent(entityId);
        auto entity = Application::Get().GetRegistry().get<EntityType>(entityId);
        auto currentAnimationName = animatorComponent.currentAnimation;
        auto totalFrames = animatorComponent.totalFrames[currentAnimationName];
        auto onAnimationEnd = animatorComponent.onAnimationEnds[currentAnimationName];
        auto currentFrame = animatorComponent.currentFrames[currentAnimationName];
        float currentTime = animatorComponent.currentTimes[currentAnimationName];
        auto textures = animatorComponent.texturesPaths[currentAnimationName];
        auto duration = animatorComponent.durations[currentAnimationName];
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
            
            Application::Get().GetRegistry().patch<AnimatorComponent>(entityId, [&](AnimatorComponent& component) 
            { 
                component.currentTimes[currentAnimationName] = currentTime;
            });
            
            std::string entityName = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(entityId)->m_name;

            Application::Get().GetRegistry().patch<AnimatorComponent>(entityId, [&](AnimatorComponent& component) 
            { 
                component.currentFrames[currentAnimationName] = currentFrame;
            });
            
            Application::Get().GetRenderer()->SetTextureIndex(entity.name, currentFrame);
        }
        else
        {
            currentTime += deltaTime;

            Application::Get().GetRegistry().patch<AnimatorComponent>(entityId, [&](AnimatorComponent& component) 
            { 
                component.currentTimes[currentAnimationName] = currentTime;
            });
        }
    }
}
