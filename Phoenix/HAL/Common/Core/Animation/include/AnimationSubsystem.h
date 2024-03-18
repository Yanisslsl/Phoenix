// AnimationSubsystem.h

#pragma once
#include <map>

#include "Core.h"
#include "ECS/include/AnimationSystem.h"

namespace Phoenix
{

    struct AnimatorComponent
    {
        std::string currentAnimation;
        std::vector<std::string> names;
        std::map<std::string, float> durations;
        std::map<std::string, float> currentTimes;
        std::map<std::string, int> currentFrames;
        std::map<std::string, int> totalFrames;
        std::map<std::string, std::vector<std::string>> texturesPaths;
    };
    
    class PHOENIX_API AnimationSubsystem
    {
    public:
        AnimationSubsystem();
        ~AnimationSubsystem();
        void CreateAnimation(EntityId entity, std::string name, int totalFrames, float duration, std::vector<std::string> pathsr);
        AnimatorComponent GetAnimatorComponent(EntityId entity);
        void UpdateAnimation(EntityId entity);
        void PlayAnimation(EntityId entity, std::string name, std::function<void()> onAnimationEnd);
        void Update();
        // void StopAnimation(EntityId entity);
        // void PauseAnimation(EntityId entity);
        // void ResumeAnimation(EntityId entity);

    private:
        AnimationSystem* m_AnimationSystem;
    };
}
