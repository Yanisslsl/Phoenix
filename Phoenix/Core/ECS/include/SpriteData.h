#pragma once
#include <string>

#include "ComponentsData.h"
#include "EntityComponent.h"
#include "Utils/Color.h"


namespace Phoenix
{
    /**
     * @brief SpriteData class
     *        SpriteData class is a class that holds the data for the sprite component
     */
    class SpriteData: public ComponentsData
    {
    public:
        SpriteData(size_t size);
        ComponentsDataType<std::string> m_spritePaths;
        ComponentsDataType<ColorCode> m_colors;
        ComponentsDataType<EntityId> m_entityIds;
    };
}
