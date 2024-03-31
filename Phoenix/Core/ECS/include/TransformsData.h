#pragma once
#include <string>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "EntityComponent.h"

#include "ComponentsData.h"

namespace Phoenix
{
    class TransformsData : public Phoenix::ComponentsData
    {
    public:
        /**
         * Create the holder of transforms data with the max number of transform it can handle
         */
        TransformsData(size_t size);
        ComponentsDataType<glm::vec3> m_positions;
        ComponentsDataType<float> m_rotations;
        ComponentsDataType<glm::vec2> m_scales;
        ComponentsDataType<EntityId> m_parents;
        ComponentsDataType<std::vector<EntityId>> m_children;
        ComponentsDataType<std::string> m_entitiesIds;
    };
}

