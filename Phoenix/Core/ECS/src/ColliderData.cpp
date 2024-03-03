#include "ECS/include/ColliderData.h"

namespace Phoenix
{
    ColliderData::ColliderData(size_t size):ComponentsData()
    {
        m_types.resize(size);
        m_coordinates.resize(size);
        m_parents.resize(size);
        m_children.resize(size);
        m_shapes.resize(size);
        m_onHitCallbacks.resize(size);
    }
}
