// AnimationSubsystem.h

#pragma once
#include <map>

#include "Core.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "ECS/include/AnimationSystem.h"

namespace Phoenix
{

    struct AnimatorComponent: public IComponent
    {
        AnimatorComponent() = default;
        AnimatorComponent(std::string name, std::vector<std::string> names, std::map<std::string, float> durations, std::map<std::string, float> currentTimes, std::map<std::string, int> currentFrames, std::map<std::string, int> totalFrames, std::map<std::string, std::vector<std::string>> texturesPaths):
        currentAnimation(name), names(names), durations(durations), currentTimes(currentTimes), currentFrames(currentFrames), totalFrames(totalFrames), texturesPaths(texturesPaths)
        {
        }
        std::string currentAnimation;
        std::vector<std::string> names;
        std::map<std::string, float> durations;
        std::map<std::string, float> currentTimes;
        std::map<std::string, int> currentFrames;
        std::map<std::string, int> totalFrames;
        std::map<std::string, std::vector<std::string>> texturesPaths;
        virtual void Serialize(BlobSerializer& serializer) override
        {
            
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            
        }
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
