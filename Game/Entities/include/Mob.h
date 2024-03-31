// Mob.h

#pragma once
#include <string>

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"

class Mob
{
public:
    /**
     * Instantiate a new mob with position, target and name
     */
    Mob(glm::vec2 position, Phoenix::Ref<Phoenix::Entity> target, std::string _name);
    ~Mob();
    void OnUpdate();
    /**
     * Method called when the mob collide with something. This something is passed as parameter.
     */
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    void OnDeath();
    /**
     * Return if the entity is dead or not
     */
    bool GetIsDead();
    /**
     * Return the entity name
     */
    std::string GetEntityName();
private:
    std::string m_name;
    float speed;
    int health;
    std::string m_id;
    int damage;
    Phoenix::Ref<Phoenix::Entity> m_target;
    bool isDead;
};
