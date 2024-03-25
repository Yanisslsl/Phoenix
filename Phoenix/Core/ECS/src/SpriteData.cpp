#include "ECS/include/SpriteData.h"

namespace Phoenix
{
    SpriteData::SpriteData(size_t size):ComponentsData()
    {
        m_spritePaths.resize(size);
        m_colors.resize(size);
        m_entityIds.resize(size, -1);
    }
}
