#pragma once
#include "Base/Base.h"
#include "Core/ECSExtended/include/Entity.h"
#include "Bullet.h"

class Knight: public Phoenix::ISerializable, public Phoenix::AutoRegister<Knight>
{
    enum class State
    {
        IDLE,
        RUN_RIGHT,
        RUN_LEFT,
        FIRE_RIGHT,
        FIRE_LEFT,
    };
public:
    Knight();
    ~Knight();
    void UpdateInput();
    void GetMovementInput();
    void GetFireInput();
    void OnStart();
    void Move();
    void Update();
    void PlayAnimation();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    void Fire();
    void Serialize(Phoenix::BlobSerializer& serializer) override;
    void Deserialize(Phoenix::BlobSerializer& serializer) override;
private:
    float m_X_Direction = 0;
    float m_Y_Direction = 0;
    float m_Speed = 3.0f;
    int m_count = 0;
    int m_BulletCount = 0;
    glm::vec2 m_Position;
    std::string m_name;
    State m_State = State::IDLE;
    bool m_isStateDirty = false;
    REGISTER_CLASS_WITH_FACTORY(Knight)
};
