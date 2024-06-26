
#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Core.h"
#include "IComponent.h"

namespace Phoenix
{
    /**
     * \brief TransformComponent class that represent a transform component in the game.
     */
    class PHOENIX_API TransformComponent: public IComponent, AutoRegister<TransformComponent>
    {
    public:
        TransformComponent() = default;
        TransformComponent(glm::vec3 position, float rotation, glm::vec3 scale, glm::vec3 rotationAxis = glm::vec3(1.0f, 1.0f, 0.0f)):
           position(position), rotation(rotation), scale(scale), rotationAxis(rotationAxis)
        {
        }
        glm::vec3 position;
        float rotation;
        glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 scale;
     
        EntityIdentifier entityId;
        virtual void Serialize(BlobSerializer& serializer) override
        {
            // serializer.WriteHeader(TransformComponentSerializeType);
            // serializer.Write(&position, sizeof(position));
            // serializer.Write(&rotation, sizeof(rotation));
            // serializer.Write(&scale, sizeof(scale));
            // serializer.Write(&entityId, sizeof(entityId));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            // serializer.Read(&position, sizeof(position));
            // serializer.Read(&rotation, sizeof(rotation));
            // serializer.Read(&scale, sizeof(scale));
            // serializer.Read(&entityId, sizeof(entityId));
        }

        virtual bool IsValid() override
        {
            if(position == glm::vec3(0.0f) && rotation == 0.0f && scale == glm::vec3(0.0f))
            {
                return false;
            }
            return true;
        }
    };

    /**
     * \brief TransformSubsytem class that represent a transform subsystem in the game.
     */
    class PHOENIX_API TransformSubsytem
    {
    public:
        TransformSubsytem();
        ~TransformSubsytem();
        /**
         * \brief Add a transform component to the entity
         * \param id EntityIdentifier to add
         * \param component TransformComponent to add
         */
        void AddTransformComponent(EntityIdentifier id, TransformComponent component);

        /**
         * \brief Check if entity has transform component
         * \param id EntityIdentifier to check
         * \return bool
         */
        bool HasTransformComponent(EntityIdentifier id);

        /**
         * \brief Get transform component of entity
         * \param id EntityIdentifier to get
         * \return TransformComponent
         */
        TransformComponent GetTransformComponent(EntityIdentifier id);

        /**
         * \brief Delete transform component of entity
         * \param id EntityIdentifier to delete
         */
        void DeleteTransformComponent(EntityIdentifier id);

        /**
         * \brief Set transform position of entity
         * \param id EntityIdentifier to set
         * \param position position to set
         */
        void SetTransformPosition(EntityIdentifier id, glm::vec3 position);

        /**
         * \brief Set transform rotation of entity
         * \param id EntityIdentifier to set
         * \param rotation rotation to set
         */
        void SetTransformRotation(EntityIdentifier id, float rotation);


        /**
         * \brief Set transform rotation of entity
         * \param id EntityIdentifier to set
         * \param rotation rotation to set
         * \param axis axis to set
         */
        void SetTransformRotation(EntityIdentifier id, float rotation, glm::vec3 axis);

        /**
         * \brief Set transform scale of entity
         * \param id EntityIdentifier to set
         * \param scale scale to set
         */
        void SetTransformScale(EntityIdentifier id, glm::vec3 scale);

        /**
         * \brief Set transform scale of entity
         * \param id EntityIdentifier to set
         * \param scale scale to set
         */
        void SetTransformScale(EntityIdentifier id, glm::vec2 scale);


        /**
         * \brief Get transform position of entity
         * \param id EntityIdentifier to get
         * \return glm::vec3
         */
        glm::vec3 GetTransformPosition(EntityIdentifier id);

        /**
         * \brief Get transform rotation of entity
         * \param id EntityIdentifier to get
         * \return float
         */
        float GetTransformRotation(EntityIdentifier id);

        /**
         * \brief Get transform rotation axis of entity
         * \param id 
         * \return 
         */
        glm::vec3 GetTransformRotationAxis(EntityIdentifier id);

        /**
         * \brief Get transform scale of entity
         * \param id EntityIdentifier to get
         * \return glm::vec2
         */
        glm::vec3 GetTransformScale(EntityIdentifier id);
    };
}
