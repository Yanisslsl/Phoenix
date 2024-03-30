// Mob.h

#pragma once
#include <string>

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"

class Mob
{
public:
    Mob(glm::vec2 position, Phoenix::Ref<Phoenix::Entity> target, std::string _name);
    ~Mob();
    void OnUpdate();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    void OnDeath();
    bool GetIsDead();
    std::string GetEntityName();
private:
    std::string m_name;
    float speed;
    int health;
    std::string m_id;
    int damage;
    Phoenix::Ref<Phoenix::Entity> m_target;
    bool isDead;
    float dt;
};
