// ColliderSystem.h

#pragma once
#include "ColliderData.h"
#include "ComponentSystem.h"
#include "Core.h"
namespace Phoenix
{
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
    
            CollisionType GetColliderType(EntityId entity);
            void SetColliderType(EntityId entity, CollisionType type);
            void SetColliderCoordinates(EntityId entity, ColliderCoordinates coordinates);
            void SetOnHitCallback(EntityId entity, std::function<void(void*)> callback);
            std::function<void(void*)> GetOnHitCallback(EntityId entity);
            ColliderCoordinates GetColliderCoordinates(EntityId entity);
            ColliderData* m_ColliderData;
        };
    }

