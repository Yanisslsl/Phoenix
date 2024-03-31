#pragma once
#include <functional>
#include <string>
#include <glm/vec2.hpp>

#include "ComponentsData.h"
#include "Core/ECSExtended/include/Entity.h"

namespace Phoenix
{
    struct BoxCollider;
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

    /**
       * @brief ColliderData class
       * 
       */
    class ColliderData: public ComponentsData
    {
    public:
        ColliderData(size_t size);
        ComponentsDataType<CollisionType> m_types;
        ComponentsDataType<float> m_heights;
        ComponentsDataType<float> m_widths;
        ComponentsDataType<glm::vec2> m_positions;
        ComponentsDataType<std::function<void(Ref<Entity>)>> m_onHitCallbacks;
        ComponentsDataType<CollisionShape> m_shapes;
        ComponentsDataType<EntityId> m_entities;
        ComponentsDataType<std::string> m_nodeIds;
        ComponentsDataType<int> m_hitCalls;
    };
}
