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
    
            ColliderSystem(ComponentSystemId id, size_t dataSize);
            ~ColliderSystem() override;
            virtual void Init() override;
            virtual void Start() override;
            virtual void Update() override;
            std::vector<EntityId> GetCollidersEntitiesIds();
            virtual void DeleteComponent(EntityId entity) override;
            bool HasCollider(EntityId entity);
            CollisionType GetColliderType(EntityId entity);
            void SetColliderType(EntityId entity, CollisionType type);
            void SetColliderPosition(EntityId entity, glm::vec2 position);
            void SetColliderWidth(EntityId entity, float width);
            void SetColliderHeight(EntityId entity, float height);
            void SetOnHitCallback(EntityId entity, std::function<void(Ref<Entity>)> onHitCallback);
            void SetColliderEntity(EntityId entity, EntityId colliderEntity);
            void SetColliderNodeId(EntityId entity, std::string nodeId);
            void SetColliderHitCalls(EntityId entity, int hitCalls);
            int GetColliderHitCalls(EntityId entity);
            std::string GetColliderNodeId(EntityId entity);
            EntityId GetColliderEntity(EntityId entity);
            std::function<void(Ref<Entity>)> GetOnHitCallback(EntityId entity);
            glm::vec2 GetColliderPosition(EntityId entity);
            float GetColliderWidth(EntityId entity);
            float GetColliderHeight(EntityId entity);
        private: 
            ColliderData* m_ColliderData;
        };
    }

