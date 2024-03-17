// Bullet.h

#pragma once
#include <glm/vec2.hpp>

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"

class Bullet
{
public:
    Bullet(std::string id, glm::vec2 position, glm::vec2 direction);
    ~Bullet();
    void Update();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    std::string m_id;
private:
    glm::vec2 m_Direction;
    float m_Speed = 5.0f;
    Phoenix::Ref<Phoenix::Entity> self;
};
