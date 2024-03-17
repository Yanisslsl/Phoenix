// Isac.h

#pragma once
#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "Bullet.h"
class Knight
{
public:
    Knight();
    ~Knight();
    void UpdateInput();
    void GetMovementInput();
    void GetFireInput();
    void Update();
    void OnHit(Phoenix::Ref<Phoenix::Entity> entity);
    void Fire();
private:
    float m_X_Direction = 0;
    float m_Y_Direction = 0;
    float m_Speed = 3.0f;
    int m_count = 0;
    int m_BulletCount = 0;
    std::vector<Bullet*> m_Bullets;
};
