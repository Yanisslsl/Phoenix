// TransformSubsytem.h

#pragma once
#include "ECS/include/TransformSystem.h"
#include "Core.h"
#include "Entity.h"
#include "Common/Core/Serialization/include/BlobSerializer.h"

namespace Phoenix
{
    class PHOENIX_API TransformComponent: public IComponent
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
        virtual void Serialize(BlobSerializer& serializer) override
        {
            
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            
        }
    };
    
    class PHOENIX_API TransformSubsytem
    {
    public:
        TransformSubsytem();
        ~TransformSubsytem();
        void AddTransformComponent(EntityId id, TransformComponent component);
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
