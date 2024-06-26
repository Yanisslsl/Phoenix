﻿#pragma once
#include <glm/vec2.hpp>

#include "Base/Base.h"
#include "Core/ECSExtended/include/Entity.h"

class Bullet : public Phoenix::ISerializable, public Phoenix::AutoRegister<Bullet>
{
public:
    Bullet();
    ~Bullet();
    Bullet(std::string id, glm::vec2 position, glm::vec2 direction);
    void Update();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    std::string m_id;
     void Serialize(Phoenix::BlobSerializer& serializer) override {}
    void Deserialize(Phoenix::BlobSerializer& serializer) override {}
private:
    glm::vec2 m_Direction;
    float m_Speed = 5.0f;
    Phoenix::Ref<Phoenix::Entity> self;
};
