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
    /**
     * @brief TransformsData class
     *         TransformsData class is a class that holds the data for the transform component
     */
    class TransformsData : public Phoenix::ComponentsData
    {
    public:
        TransformsData(size_t size);
        ComponentsDataType<glm::vec3> m_positions;
        ComponentsDataType<float> m_rotations;
        ComponentsDataType<glm::vec2> m_scales;
        ComponentsDataType<EntityId> m_parents;
        ComponentsDataType<std::vector<EntityId>> m_children;
        ComponentsDataType<EntityId> m_entitiesIds;
    };
}

