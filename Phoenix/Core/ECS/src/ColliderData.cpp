#include "ECS/include/ColliderData.h"

namespace Phoenix
{
    ColliderData::ColliderData(size_t size):ComponentsData()
    {
        m_types.resize(size);
        m_heights.resize(size);
        m_widths.resize(size);
        m_positions.resize(size);
        m_shapes.resize(size);
        m_onHitCallbacks.resize(size);
        m_entities.resize(size);
        m_nodeIds.resize(size);
        m_hitCalls.resize(size);
    }
}
