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
     * @refacto: subject to change in the future
     */
    struct AnimatorComponent: IComponent, AutoRegister<AnimatorComponent>
    {
        AnimatorComponent() = default;
        std::string currentAnimation;
        std::vector<std::string> names;
        std::map<std::string, float> durations;
        std::map<std::string, float> currentTimes;
        std::map<std::string, int> currentFrames;
        std::map<std::string, int> totalFrames;
        std::map<std::string, std::vector<std::string>> texturesPaths;
        std::map<std::string, std::function<void()>> onAnimationEnds;
        virtual void Serialize(BlobSerializer& serializer) override
        {
            // serializer.WriteHeader(AnimatorComponentSerializeType);
            // serializer.Write(&currentAnimation, sizeof(currentAnimation));
            // serializer.Write(&names, sizeof(names));
            // serializer.Write(&durations, sizeof(durations));
            // serializer.Write(&currentTimes, sizeof(currentTimes));
            // serializer.Write(&currentFrames, sizeof(currentFrames));
            // serializer.Write(&totalFrames, sizeof(totalFrames));
            // serializer.Write(&texturesPaths, sizeof(texturesPaths));
            // serializer.Write(&entityId, sizeof(entityId));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            // serializer.Read(&currentAnimation, sizeof(currentAnimation));
            // serializer.Read(&names, sizeof(names));
            // serializer.Read(&durations, sizeof(durations));
            // serializer.Read(&currentTimes, sizeof(currentTimes));
            // serializer.Read(&currentFrames, sizeof(currentFrames));
            // serializer.Read(&totalFrames, sizeof(totalFrames));
            // serializer.Read(&texturesPaths, sizeof(texturesPaths));
            // serializer.Read(&entityId, sizeof(entityId));
        }

        virtual bool IsValid() override
        {
           if(names.size() == 0)
           {
               return false;
           }
          return true;
        }
    };
    
    class PHOENIX_API AnimationSubsystem
    {
    public:
        AnimationSubsystem();
        ~AnimationSubsystem();

        /**
         * \brief Create an animation for the entity
         * \param entity EntityIdentifier to create animation
         * \param name Name of the animation
         * \param totalFrames Total frames of the animation
         * \param duration Duration of the animation
         * \param path Paths of the textures
         */
        void CreateAnimation(EntityIdentifier entity, std::string name, int totalFrames, float duration, std::vector<std::string> path);

        /**
         * \brief Check if entity has animation
         * \param entity EntityIdentifier to check
         * \return bool
         */
        bool HasAnimation(EntityIdentifier entity);

        /**
         * \brief Get animator component of entity
         * \param entity EntityIdentifier to get
         * \return AnimatorComponent
         */
        AnimatorComponent GetAnimatorComponent(EntityIdentifier entity);

        /**
         * \brief Update animation of entity
         * \param entity EntityIdentifier to update
         */
        void UpdateAnimation(EntityIdentifier entity);

        /**
         * \brief Play animation of entity
         * \param entity EntityIdentifier to play
         * \param name Name of the animation
         * \param onAnimationEnd Function to call when animation ends
         */
        void PlayAnimation(EntityIdentifier entity, std::string name, std::function<void()> onAnimationEnd);

        /**
         * \brief Update the animation subsystem
         */
        void Update();

        /**
         * \brief Delete animation of entity
         * \param entityId EntityIdentifier to delete
         */
        void DeleteAnimation(EntityIdentifier entityId);
    private:
    };
}
