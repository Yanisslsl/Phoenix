// TransformSubsytem.h

#pragma once
#include "ECS/include/TransformSystem.h"
#include "Core.h"
#include "Entity.h"
#include "Common/Core/Serialization/include/BlobSerializer.h"

namespace Phoenix
{
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
    
    class PHOENIX_API TransformSubsytem
    {
    public:
        TransformSubsytem();
        ~TransformSubsytem();
        void AddTransformComponent(EntityId id, TransformComponent component);
        bool HasTransformComponent(EntityId id);
        TransformComponent GetTransformComponent(EntityId id);
        void DeleteTransformComponent(EntityId id);
        void SetTransformPosition(EntityId id, glm::vec3 position);
        void SetTransformRotation(EntityId id, float rotation);
        void SetTransformScale(EntityId id, glm::vec2 scale);
        glm::vec3 GetTransformPosition(EntityId id);
        float GetTransformRotation(EntityId id);
        glm::vec2 GetTransformScale(EntityId id);
    private:
        TransformSystem* m_TransformSystem;
    };
}
