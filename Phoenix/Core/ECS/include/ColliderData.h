// ColliderData.h

#pragma once
#include <functional>
#include <string>
#include <glm/vec2.hpp>

#include "ComponentsData.h"
#include "Common/Core/ECSExtended/include/Entity.h"

namespace Phoenix
{
    class BoxCollider;
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



    class ColliderData: public ComponentsData
    {
    public:
        ColliderData(size_t size);
        std::vector<CollisionType> m_types;
        // @TODO: change to std::vector<glm::vec2> m_positions; std::vector<float> m_widths; std::vector<float> m_heights;
        std::vector<float> m_heights;
        std::vector<float> m_widths;
        std::vector<glm::vec2> m_positions;
        std::vector<std::function<void(Ref<Entity>)>> m_onHitCallbacks;
        std::vector<CollisionShape> m_shapes;
        std::vector<EntityId> m_entities;
        std::vector<std::string> m_nodeIds;
        std::vector<int> m_hitCalls;
    };
}
