// TransformSubsytem.h

#pragma once
#include "ECS/include/TransformSystem.h"
#include "Core.h"

namespace Phoenix
{
    struct TransformComponent
    {
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    };
    
    class PHOENIX_API TransformSubsytem
    {
    public:
        TransformSubsytem();
        ~TransformSubsytem();
        void AddTransformComponent(EntityId id, TransformComponent component);
        void SetTransformPosition(EntityId id, glm::vec2 position);
        void SetTransformRotation(EntityId id, float rotation);
        void SetTransformScale(EntityId id, glm::vec2 scale);
        glm::vec2 GetTransformPosition(EntityId id);
        float GetTransformRotation(EntityId id);
        glm::vec2 GetTransformScale(EntityId id);
    private:
        TransformSystem* m_TransformSystem;
    };
}
