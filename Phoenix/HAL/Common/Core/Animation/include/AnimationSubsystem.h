// AnimationSubsystem.h

#pragma once
#include <map>

#include "Core.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "ECS/include/AnimationSystem.h"

namespace Phoenix
{

    struct AnimatorComponent: IComponent, AutoRegister<AnimatorComponent>
    {
        AnimatorComponent() = default;
        AnimatorComponent(EntityId entityId, std::string name, std::vector<std::string> names, std::map<std::string, float> durations, std::map<std::string, float> currentTimes, std::map<std::string, int> currentFrames, std::map<std::string, int> totalFrames, std::map<std::string, std::vector<std::string>> texturesPaths):
        entityId(entityId), currentAnimation(name), names(names), durations(durations), currentTimes(currentTimes), currentFrames(currentFrames), totalFrames(totalFrames), texturesPaths(texturesPaths)
        {
        }
        std::string currentAnimation;
        std::vector<std::string> names;
        std::map<std::string, float> durations;
        std::map<std::string, float> currentTimes;
        std::map<std::string, int> currentFrames;
        std::map<std::string, int> totalFrames;
        std::map<std::string, std::vector<std::string>> texturesPaths;
        EntityId entityId;
        virtual void Serialize(BlobSerializer& serializer) override
        {
            serializer.WriteHeader(AnimatorComponentSerializeType);
            serializer.Write(&currentAnimation, sizeof(currentAnimation));
            serializer.Write(&names, sizeof(names));
            serializer.Write(&durations, sizeof(durations));
            serializer.Write(&currentTimes, sizeof(currentTimes));
            serializer.Write(&currentFrames, sizeof(currentFrames));
            serializer.Write(&totalFrames, sizeof(totalFrames));
            serializer.Write(&texturesPaths, sizeof(texturesPaths));
            serializer.Write(&entityId, sizeof(entityId));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            serializer.Read(&currentAnimation, sizeof(currentAnimation));
            serializer.Read(&names, sizeof(names));
            serializer.Read(&durations, sizeof(durations));
            serializer.Read(&currentTimes, sizeof(currentTimes));
            serializer.Read(&currentFrames, sizeof(currentFrames));
            serializer.Read(&totalFrames, sizeof(totalFrames));
            serializer.Read(&texturesPaths, sizeof(texturesPaths));
            serializer.Read(&entityId, sizeof(entityId));
        }
    private:
        //REGISTER_CLASS_WITH_FACTORY(AnimatorComponent)
    };
    
    class PHOENIX_API AnimationSubsystem
    {
    public:
        AnimationSubsystem();
        ~AnimationSubsystem();
        void CreateAnimation(EntityId entity, std::string name, int totalFrames, float duration, std::vector<std::string> pathsr);
        bool HasAnimation(EntityId entity);
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
