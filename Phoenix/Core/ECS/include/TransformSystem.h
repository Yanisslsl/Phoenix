#pragma once
#include <glm/vec2.hpp>

#include "ComponentSystem.h"
#include "TransformsData.h"
#include "../../../Core/Core.h"
#include <glm/ext/matrix_transform.hpp>

//class TransformsData;

namespace Phoenix
{
    class PHOENIX_API TransformSystem final : public ComponentSystem
    {
    public:
        void InitComponents() override;
        void StartComponents() override;
        void UpdateComponents() override;
        
        TransformSystem(ComponentSystemId id, size_t dataSize);
        ~TransformSystem() override;
        void DeleteComponentFrom(EntityId entity) override;
        
        virtual void Init() override;
        virtual void Start() override;
        virtual void Update() override;

        TransformsData* m_TransformsData;

        glm::vec3 GetEntityPosition(EntityId entity);
        void SetEntityPostion(EntityId entity, glm::vec3 position);
        void PrintEntityPosition(EntityId entity);

        void SetEntityRotation(EntityId entity, float rotation);
        float GetEntityRotation(EntityId entity);
        
        void SetEntityScale(EntityId entity, glm::vec2 scale);
        glm::vec2 GetEntityScale(EntityId entity);
    }; 
}

