// Mob.h

#pragma once
#include <string>

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"

class Mob
{
public:
    Mob(glm::vec2 position);
    ~Mob();
    void OnUpdate();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    void OnDeath();
private:
    float speed;
    int health;
    std::string m_id;
    int damage;
};
