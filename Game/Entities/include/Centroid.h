#pragma once

#pragma once
#include "Base/Base.h"
#include "ECSExtended/include/Entity.h"

class Centroid
{
public:
    Centroid();
    Phoenix::Ref<Phoenix::Entity> GetManagedSelfEntity() { return self; }
    void SetDirection(glm::vec3 direction) { m_Direction = direction; }
    glm::vec3 GetDirection() { return m_Direction; }
    void Update();
    void SetSpeed(float speed) { m_Speed = speed; }
    float GetSpeed() { return m_Speed; }
    float GetMaxSpeed() { return m_MaxSpeed; }
    void RotateBoidBasedOnDirection();
private:
    glm::vec3 m_Direction = glm::vec3(0,0,-1.0);
    float m_Speed = 2.0f;
    float m_MaxSpeed = 1.0f;
    Phoenix::Ref<Phoenix::Entity> self;
    std::string m_id;
};
