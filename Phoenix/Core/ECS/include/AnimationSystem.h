#pragma once
#include "AnimationData.h"
#include "ComponentSystem.h"
#include "Core.h"
namespace Phoenix
{
    /**
     * @brief AnimationSystem class registry
     * 
     */
    class PHOENIX_API AnimationSystem final: public ComponentSystem
    {
    public:
        void InitComponents() override;
        void StartComponents() override;
        void UpdateComponents() override;

        AnimationSystem(ComponentSystemId id, size_t dataSize);
        ~AnimationSystem() override;
        virtual void Init() override;
        virtual void Start() override;
        virtual void Update() override;

        void DeleteComponent(EntityId entity) override;

        bool HasAnimation(EntityId entity);
        void SetAnimationsEntityId(EntityId entity);

        std::vector<EntityId> GetEntitiesWithAnimation();

        void SetCurrentAnimationName(EntityId entity, std::string name);
        std::string GetCurrentAnimationName(EntityId entity);
        
        void SetAnimationName(EntityId entity, std::string name);
        std::vector<std::string> GetAnimationsNames(EntityId entity);

        void SetAnimationDuration(EntityId entity, std::string animationName, float duration);
        float GetAnimationDuration(EntityId entity, std::string animationName);
        std::map<std::string, float> GetAnimationsDurations(EntityId entity);

        void SetAnimationCurrentTime(EntityId entity, std::string animationName, float time);
        float GetAnimationCurrentTime(EntityId entity, std::string animationName);
        std::map<std::string, float> GetAnimationsCurrentTimes(EntityId entity);

        void SetAnimationCurrentFrame(EntityId entity, std::string animationName, int frame);
        int GetAnimationCurrentFrame(EntityId entity, std::string animationName);
        std::map<std::string, int> GetAnimationsCurrentFrames(EntityId entity);

        void SetAnimationTotalFrames(EntityId entity, std::string animationName, int totalFrames);
        int GetAnimationTotalFrames(EntityId entity, std::string animationName);
        std::map<std::string, int> GetAnimationsTotalFrames(EntityId entity);

        std::vector<std::string> GetAnimationTexturesPaths(EntityId entity, std::string animationName);
        void SetAnimationTexturesPaths(EntityId entity, std::string animationName, std::vector<std::string> texturesPaths);
        std::map<std::string, std::vector<std::string>> GetAnimationsTexturesPaths(EntityId entity);

        void SetOnAnimationEnd(EntityId entity, std::string animationName, std::function<void()> onAnimationEnd);
        std::function<void()> GetOnAnimationEnd(EntityId entity, std::string animationName);
    private:
        AnimationData* m_AnimationData;
    };
}
