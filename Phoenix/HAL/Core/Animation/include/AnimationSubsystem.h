#pragma once
#include <map>

#include "Core.h"
#include "Core/ECSExtended/include/Entity.h"
#include "ECS/include/AnimationSystem.h"
#include "Core/Serialization/include/BlobSerializer.h"

namespace Phoenix
{

    /**
     * \brief AnimatorComponent class that represent a animator component in the game.
     */
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
    };
    
    class PHOENIX_API AnimationSubsystem
    {
    public:
        AnimationSubsystem();
        ~AnimationSubsystem();

        /**
         * \brief Create an animation for the entity
         * \param entity EntityId to create animation
         * \param name Name of the animation
         * \param totalFrames Total frames of the animation
         * \param duration Duration of the animation
         * \param path Paths of the textures
         */
        void CreateAnimation(EntityId entity, std::string name, int totalFrames, float duration, std::vector<std::string> path);

        /**
         * \brief Check if entity has animation
         * \param entity EntityId to check
         * \return bool
         */
        bool HasAnimation(EntityId entity);

        /**
         * \brief Get animator component of entity
         * \param entity EntityId to get
         * \return AnimatorComponent
         */
        AnimatorComponent GetAnimatorComponent(EntityId entity);

        /**
         * \brief Update animation of entity
         * \param entity EntityId to update
         */
        void UpdateAnimation(EntityId entity);

        /**
         * \brief Play animation of entity
         * \param entity EntityId to play
         * \param name Name of the animation
         * \param onAnimationEnd Function to call when animation ends
         */
        void PlayAnimation(EntityId entity, std::string name, std::function<void()> onAnimationEnd);

        /**
         * \brief Update the animation subsystem
         */
        void Update();

        /**
         * \brief Delete animation of entity
         * \param entityId EntityId to delete
         */
        void DeleteAnimation(EntityId entityId);
    private:
        AnimationSystem* m_AnimationSystem;
    };
}
