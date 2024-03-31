// ColliderSystem.h

#pragma once
#include <string>

#include "ColliderData.h"
#include "ComponentSystem.h"
#include "Core.h"

namespace Phoenix
{
        class BoxCollider;
        class PHOENIX_API ColliderSystem final: public ComponentSystem
        {
        public:
            void InitComponents() override;
            void StartComponents() override;
            void UpdateComponents() override;
            /**
             * \brief The system that manage collision between entities
             */
            ColliderSystem(ComponentSystemId id, size_t dataSize);
            ~ColliderSystem() override;
            virtual void Init() override;
            virtual void Start() override;
            virtual void Update() override;

            /**
             * \brief Delete the component from the passed entity
             */
            virtual void DeleteComponent(EntityId entity) override;
            bool HasCollider(EntityId entity);

            /**
             * \brief Returns the collider type for the passed entity
             */
            CollisionType GetColliderType(EntityId entity);
            /**
             * \brief Set the passed collider type for the passed entity
             */
            void SetColliderType(EntityId entity, CollisionType type);
            /**
             * \brief Set the collider postion for the passed entity
             */
            void SetColliderPosition(EntityId entity, glm::vec2 position);
            /**
             * \brief Set the collider width for the passed entity
             */
            void SetColliderWidth(EntityId entity, float width);
            /**
             * \brief Set the collider height for the passed entity
             */
            void SetColliderHeight(EntityId entity, float height);
            /**
             * \brief Set a callback method when the collider hits another
             */
            void SetOnHitCallback(EntityId entity, std::function<void(Ref<Entity>)> onHitCallback);
            
            void SetColliderEntity(EntityId entity, EntityId colliderEntity);
            void SetColliderNodeId(EntityId entity, std::string nodeId);
            void SetColliderHitCalls(EntityId entity, int hitCalls);
            int GetColliderHitCalls(EntityId entity);
            /**
             * \brief Returns the id of the collision node for the passed entity
             */
            std::string GetColliderNodeId(EntityId entity);
            /**
             * \brief Returns the collider entity for the passed entity 
             */
            EntityId GetColliderEntity(EntityId entity);
            /**
             * \brief Returns the callback method currently set for the passed entity
             */
            std::function<void(Ref<Entity>)> GetOnHitCallback(EntityId entity);
            /**
             * \brief Returns the collider position for the passed entity
             */
            glm::vec2 GetColliderPosition(EntityId entity);
            /**
             * \brief Returns the collider width for the passed entity
             */
            float GetColliderWidth(EntityId entity);
            /**
             * \brief Returns the collider height for the passed entity
             */
            float GetColliderHeight(EntityId entity);
        private: 
            ColliderData* m_ColliderData;
        };
    }

