#pragma once
#include <glm/vec3.hpp>

#include "../../Entities/include/Centroid.h"
#include "Base/Base.h"
#include "ECSExtended/include/Entity.h"
#include "../../Entities/include/Boid.h"



class BoidManager
{
public:
    BoidManager();
    void Update();
    void UpdateBoids();
    void Test();

    float GetSeparationWeight() const { return m_SeparationWeight; }
    void SetSeparationWeight(float weight) { m_SeparationWeight = weight; }

    float GetCohesionWeight() const { return m_CohesionWeight; }
    void SetCohesionWeight(float weight) { m_CohesionWeight = weight; }

    float GetAlignmentWeight() const { return m_AlignmentWeight; }
    void SetAlignmentWeight(float weight) { m_AlignmentWeight = weight; }

    float GetInertiaWeight() const { return m_InertiaWeight; }
    void SetInertiaWeight(float weight) { m_InertiaWeight = weight; }

    glm::vec3 GetCentroidDirection() const { return m_Centroid->GetDirection(); }
    void SetCentroidDirection(glm::vec3 direction) { m_Centroid->SetDirection(direction); }

    float GetCentroidSpeed() const { return m_Centroid->GetSpeed(); }
    void SetCentroidSpeed(float speed);

    float GetMaxDistance() const { return maxDistance; }
    void SetMaxDistance(float distance) { maxDistance = distance; }

    void FollowCentroid();
private:
    std::vector<Phoenix::Ref<Boid>> m_Boids;
    Phoenix::Ref<Centroid> m_Centroid = nullptr;
    int counter = 0;
    float maxDistance = 5;
    float m_SeparationWeight = 1.5f;
    float m_CohesionWeight = 1.0f;
    float m_AlignmentWeight = 1.0f;
    float m_InertiaWeight = 1.0f;
};
