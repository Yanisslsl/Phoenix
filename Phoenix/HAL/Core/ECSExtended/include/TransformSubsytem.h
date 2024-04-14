
#pragma once
#include "ECS/include/TransformSystem.h"
#include "Core.h"
#include "Entity.h"
#include "Core/Serialization/include/BlobSerializer.h"

namespace Phoenix
{
    /**
     * \brief TransformComponent class that represent a transform component in the game.
     */
    class PHOENIX_API TransformComponent: public IComponent, AutoRegister<TransformComponent>
    {
    public:
        TransformComponent() = default;
        TransformComponent(glm::vec3 position, float rotation, glm::vec2 scale):
        position(position), rotation(rotation), scale(scale)
        {
        }
        glm::vec3 position;
        float rotation;
        glm::vec2 scale;
        EntityId entityId;
        virtual void Serialize(BlobSerializer& serializer) override
        {
            serializer.WriteHeader(TransformComponentSerializeType);
            serializer.Write(&position, sizeof(position));
            serializer.Write(&rotation, sizeof(rotation));
            serializer.Write(&scale, sizeof(scale));
            serializer.Write(&entityId, sizeof(entityId));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            serializer.Read(&position, sizeof(position));
            serializer.Read(&rotation, sizeof(rotation));
            serializer.Read(&scale, sizeof(scale));
            serializer.Read(&entityId, sizeof(entityId));
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
         * \param id EntityId to add
         * \param component TransformComponent to add
         */
        void AddTransformComponent(EntityId id, TransformComponent component);

        /**
         * \brief Check if entity has transform component
         * \param id EntityId to check
         * \return bool
         */
        bool HasTransformComponent(EntityId id);

        /**
         * \brief Get transform component of entity
         * \param id EntityId to get
         * \return TransformComponent
         */
        TransformComponent GetTransformComponent(EntityId id);

        /**
         * \brief Delete transform component of entity
         * \param id EntityId to delete
         */
        void DeleteTransformComponent(EntityId id);

        /**
         * \brief Set transform position of entity
         * \param id EntityId to set
         * \param position position to set
         */
        void SetTransformPosition(EntityId id, glm::vec3 position);

        /**
         * \brief Set transform rotation of entity
         * \param id EntityId to set
         * \param rotation rotation to set
         */
        void SetTransformRotation(EntityId id, float rotation);

        /**
         * \brief Set transform scale of entity
         * \param id EntityId to set
         * \param scale scale to set
         */
        void SetTransformScale(EntityId id, glm::vec2 scale);

        /**
         * \brief Get transform position of entity
         * \param id EntityId to get
         * \return glm::vec3
         */
        glm::vec3 GetTransformPosition(EntityId id);

        /**
         * \brief Get transform rotation of entity
         * \param id EntityId to get
         * \return float
         */
        float GetTransformRotation(EntityId id);

        /**
         * \brief Get transform scale of entity
         * \param id EntityId to get
         * \return glm::vec2
         */
        glm::vec2 GetTransformScale(EntityId id);
    private:
        TransformSystem* m_TransformSystem;
    };
}
