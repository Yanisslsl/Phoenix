#pragma once
#include <string>

#include "ComponentsData.h"
#include "Utils/Color.h"


namespace Phoenix
{
    class SpriteData: public ComponentsData
    {
    public:
        SpriteData(size_t size);
        ComponentsDataType<std::string> m_spritePaths;
        ComponentsDataType<ColorCode> m_colors;
        ComponentsDataType<EntityId> m_entityIds;
    };
}
