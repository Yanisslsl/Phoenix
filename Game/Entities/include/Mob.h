// Mob.h

#pragma once
#include <string>

#include "Base/Base.h"
#include "Core/ECSExtended/include/Entity.h"

class Mob: public Phoenix::ISerializable, public Phoenix::AutoRegister<Mob>
{
public:
    Mob();
    Mob(std::string& id, glm::vec2 position);
    ~Mob();
    void OnUpdate();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    void OnStart();
    void OnDeath();
    bool GetIsDead();
    std::string GetId()
    {
        return m_id;
    }
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
    float dt;
    glm::vec3 m_Position;
    REGISTER_CLASS_WITH_FACTORY(Mob)
};
