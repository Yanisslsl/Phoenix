// Mob.h

#pragma once
#include <string>

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"

class Mob: public Phoenix::ISerializable, public Phoenix::AutoRegister<Mob>
{
public:
    /**
     * Instantiate a new mob with position, target and name
     */
    Mob();
    Mob(std::string& id, glm::vec2 position);
    ~Mob();
    void OnUpdate();
    /**
     * Method called when the mob collide with something. This something is passed as parameter.
     */
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    void OnStart();
    void OnDeath();
    /**
     * Return if the entity is dead or not
     */
    bool GetIsDead();
    std::string GetId()
    {
        return m_id;
    }
    /**
     * Return the entity name
     */
    std::string GetEntityName();
    virtual void Serialize(Phoenix::BlobSerializer& serializer);
    virtual void Deserialize(Phoenix::BlobSerializer& serializer);
private:
    bool isDead;
    float speed;
    int health;
    std::string m_id;
    int damage;
    Phoenix::Ref<Phoenix::Entity> m_target;
    glm::vec3 m_Position;
    REGISTER_CLASS_WITH_FACTORY(Mob)
};
