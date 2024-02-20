#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "EntityComponent.h"

#include "ComponentsData.h"

namespace Phoenix
{
    class TransformsData : public Phoenix::ComponentsData
    {
    public:
        TransformsData(size_t size);

        std::vector<glm::vec2> m_positions;
        std::vector<glm::vec2> m_rotations;
        std::vector<glm::vec2> m_scales;
        std::vector<EntityId> m_parents;
        std::vector<std::vector<EntityId>> m_children;
    };
}

