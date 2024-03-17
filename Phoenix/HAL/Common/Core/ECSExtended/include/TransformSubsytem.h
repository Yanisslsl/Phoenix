// TransformSubsytem.h

#pragma once
#include "ECS/include/TransformSystem.h"
#include "Core.h"

namespace Phoenix
{
    struct TransformComponent
    {
        glm::vec3 position;
        float rotation;
        glm::vec2 scale;
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
