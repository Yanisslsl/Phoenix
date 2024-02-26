#include "ECS/include/TransformsData.h"

namespace Phoenix
{
    TransformsData::TransformsData(size_t size):ComponentsData()
    {
        m_positions.resize(size);
        m_rotations.resize(size);
        m_scales.resize(size);
        m_parents.resize(size);
        m_children.resize(size);
    }
}
