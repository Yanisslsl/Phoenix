// Room.h

#pragma once
#include <string>
#include <glm/vec2.hpp>

#include "Base/Base.h"

namespace Phoenix
{
    class Entity;
}

class Room
{
public:
    Room(glm::vec2 position, glm::vec2 size);
    ~Room();
    void Update();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    std::string m_id;
};
