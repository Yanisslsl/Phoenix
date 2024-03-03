// ColliderData.h

#pragma once
#include <functional>
#include <glm/vec2.hpp>

#include "ComponentsData.h"

namespace Phoenix
{
    enum class CollisionType
    {
        STATIC,
        DYNAMIC
    };

    enum class CollisionShape
    {
        CIRCLE,
        RECTANGLE
    };

    struct ColliderCoordinates
    {
        glm::vec2 position;
        float width;
        float height;
    };

    class ColliderData: public ComponentsData
    {
    public:
        ColliderData(size_t size);
        std::vector<CollisionType> m_types;
        std::vector<ColliderCoordinates> m_coordinates;
        std::vector<EntityId> m_parents;
        std::vector<std::function<void(void*)>> m_onHitCallbacks;
        std::vector<std::vector<EntityId>> m_children;
        std::vector<CollisionShape> m_shapes;
    };
}
