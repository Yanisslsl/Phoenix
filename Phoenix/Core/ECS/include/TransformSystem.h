#pragma once
#include <glm/vec2.hpp>

#include "ComponentSystem.h"
#include "TransformsData.h"
#include "../../../Core/Core.h"

//class TransformsData;

namespace Phoenix
{
    class PHOENIX_API TransformSystem final : public Phoenix::ComponentSystem
    {
    public:
        void InitComponents() override;
        void StartComponents() override;
        void UpdateComponents() override;
        
        TransformSystem(ComponentSystemId id, size_t dataSize);
        ~TransformSystem() override;
        
        virtual void Init() override;
        virtual void Start() override;
        virtual void Update() override;

        TransformsData* m_TransformsData;

        void PrintEntityPosition(EntityId entity);

        void SetEntityPostion(EntityId entity, glm::vec2 position);
    }; 
}

