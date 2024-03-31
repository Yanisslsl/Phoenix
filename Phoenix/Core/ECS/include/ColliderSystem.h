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
             * The system that manage collision between entities
             */
            ColliderSystem(ComponentSystemId id, size_t dataSize);
            ~ColliderSystem() override;
            virtual void Init() override;
            virtual void Start() override;
            virtual void Update() override;

            /**
             * Delete the component from the passed entity
             */
            virtual void DeleteComponentFrom(EntityId entity) override;

            /**
             * Returns the collider type for the passed entity
             */
            CollisionType GetColliderType(EntityId entity);
            /**
             * Set the passed collider type for the passed entity
             */
            void SetColliderType(EntityId entity, CollisionType type);
            /**
             * Set the collider postion for the passed entity
             */
            void SetColliderPosition(EntityId entity, glm::vec2 position);
            /**
             * Set the collider width for the passed entity
             */
            void SetColliderWidth(EntityId entity, float width);
            /**
             * Set the collider height for the passed entity
             */
            void SetColliderHeight(EntityId entity, float height);
            /**
             * Set a callback method when the collider hits another
             */
            void SetOnHitCallback(EntityId entity, std::function<void(Ref<Entity>)> callback);
            void SetColliderEntity(EntityId entity, EntityId colliderEntity);
            void SetColliderNodeId(EntityId entity, std::string nodeId);
            void SetColliderHitCalls(EntityId entity, int hitCalls);
            int GetColliderHitCalls(EntityId entity);
            /**
             * Returns the id of the collision node for the passed entity
             */
            std::string GetColliderNodeId(EntityId entity);
            /**
             * Returns the collider entity for the passed entity 
             */
            EntityId GetColliderEntity(EntityId entity);
            /**
             * Returns the callback method currently set for the passed entity
             */
            std::function<void(Ref<Entity>)> GetOnHitCallback(EntityId entity);
            /**
             * Returns the collider position for the passed entity
             */
            glm::vec2 GetColliderPosition(EntityId entity);
            /**
             * Returns the collider width for the passed entity
             */
            float GetColliderWidth(EntityId entity);
            /**
             * Returns the collider height for the passed entity
             */
            float GetColliderHeight(EntityId entity);
            ColliderData* m_ColliderData;
        };
    }

