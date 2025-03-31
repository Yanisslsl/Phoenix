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
    void SpawnBoids();

    float GetSeparationWeight() const { return m_SeparationWeight; }
    void SetSeparationWeight(float weight) { m_SeparationWeight = weight; }

    float GetCohesionWeight() const { return m_CohesionWeight; }
    void SetCohesionWeight(float weight) { m_CohesionWeight = weight; }

    float GetAlignmentWeight() const { return m_AlignmentWeight; }
    void SetAlignmentWeight(float weight) { m_AlignmentWeight = weight; }

    float GetInertiaWeight() const { return m_InertiaWeight; }
    void SetInertiaWeight(float weight) { m_InertiaWeight = weight; }

    float GetAvoidanceWeight() const { return m_avoidanceWeight; }
    void SetAvoidanceWeight(float weight) { m_avoidanceWeight = weight; }

    float GetMaxDistance() const { return maxDistance; }
    void SetMaxDistance(float distance) { maxDistance = distance; }

    float GetBoidSpeed() const { return m_Speed; }
    void SetBoidSpeed(float speed);

    void CreateBoundingBox();
private:
    std::vector<Phoenix::Ref<Boid>> m_Boids;
    Phoenix::Ref<Centroid> m_Centroid = nullptr;
    Phoenix::Ref<Phoenix::Entity> m_BoundingBox = nullptr;
    int counter = 0;
    float maxDistance = 5;
    float m_SeparationWeight = 1.0f;
    float m_CohesionWeight = 1.0f;
    float m_AlignmentWeight = 1.0f;
    float m_InertiaWeight = 1.0f;
    float m_avoidanceWeight = 2.0f;
    float m_cubeSize = 20.0f;
    float m_Speed = 5.0f;
};
