// Mob.h

#pragma once
#include <string>

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"

class Mob: public Phoenix::ISerializable, public Phoenix::AutoRegister<Mob>
{
public:
    Mob();
    Mob(glm::vec2 position);
    ~Mob() = default;
    void OnUpdate();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    void OnDeath();
    void Serialize(Phoenix::BlobSerializer& serializer) override {}
    void Deserialize(Phoenix::BlobSerializer& serializer) override {}
private:
    float speed;
    int health;
    std::string m_id;
    int damage;
    REGISTER_CLASS_WITH_FACTORY(Mob)
};
