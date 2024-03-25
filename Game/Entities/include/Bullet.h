// Bullet.h

#pragma once
#include <glm/vec2.hpp>

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "Common/Core/Serialization/include/SerializerSubsystem.h"

class Bullet : public Phoenix::ISerializable, public Phoenix::AutoRegister<Bullet>
{
public:
    Bullet();
    Bullet(std::string id, glm::vec2 position, glm::vec2 direction);
    ~Bullet();
    void Update();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    std::string m_id;
     void Serialize(Phoenix::BlobSerializer& serializer) override {}
    void Deserialize(Phoenix::BlobSerializer& serializer) override {}
private:
    glm::vec2 m_Direction;
    float m_Speed = 5.0f;
    Phoenix::Ref<Phoenix::Entity> self;
    REGISTER_CLASS_WITH_FACTORY(Bullet);
};
