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

        /**
         * \brief The System that manipulate entities positions, rotations and scales
         */
        TransformSystem(ComponentSystemId id, size_t dataSize);
        ~TransformSystem() override;
        /**
         * \brief Delete the component from the passed entity
         */
        void DeleteComponent(EntityId entity) override;
        
        virtual void Init() override;
        virtual void Start() override;
        virtual void Update() override;

        TransformsData* m_TransformsData;

        void SetEntityId(EntityId entity);
        bool HasTransform(EntityId entity);

        /**
         * \brief Get the position for the passed entity
         */
        glm::vec3 GetEntityPosition(EntityId entity);
        /**
         * \brief Set the postion for the passed entity
         */
        void SetEntityPostion(EntityId entity, glm::vec3 position);
        /**
         * \brief Print the position for the passed entity
         */
        void PrintEntityPosition(EntityId entity);
        /**
         * \brief Set the rotation for the passed entity
         */
        void SetEntityRotation(EntityId entity, float rotation);
        /**
         * \brief Get the rotation for the passed entity
         */
        float GetEntityRotation(EntityId entity);
        /**
         * \brief Set the scale for the passed entity
         */
        void SetEntityScale(EntityId entity, glm::vec2 scale);
        /**
         * \brief Get the scale for the passed entity
         */
        glm::vec2 GetEntityScale(EntityId entity);
    }; 
}

