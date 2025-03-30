#pragma once
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

#include "ECSExtended/include/IComponent.h"
#include "Utils/Color.h"


class btDiscreteDynamicsWorld;

namespace Phoenix
{

    enum RigidbodyType
    {
        // The relative entity will be not affected by physics movement but is still registered in the physics world, use this for static objects or objects where you handle on your own the movement
        STATIC,
        // The relative entity will be affected by physics movement, be careful when setting location, scales, and rotations
        DYNAMIC
    };

    enum RigidBodyShape
    {
        SPHERE,
        BOX
    };

    struct HitResult
    {
        bool hasHit;
        EntityIdentifier hitEntity;
        glm::vec3 hitPosition;
        glm::vec3 hitNormal;
    };

    struct DebgugLine
    {
        float duration = 0;
        ColorCode color = Phoenix::Color::RED;
        float width = 1;
    };

    struct DebugData
    {
        std::string name;
        std::chrono::time_point<std::chrono::high_resolution_clock> expirationTime;
    };

    /**
     * @TODO: link to tag system
     */
    
    enum CollisionGroups {
        NOTHING = 0,
        GROUP_DEFAULT = 1 << 0,    // 1
        GROUP_PLAYER = 1 << 1,     // 2
        GROUP_ENEMY = 1 << 2,      // 4
        GROUP_PROJECTILE = 1 << 3, // 8
        GROUP_TRIGGER = 1 << 4,    // 16
        ALL_GROUPS = -1            // All bits to 1
    };
    
    struct PHOENIX_API RigidBody: IComponent, AutoRegister<RigidBody>
    {
    public:
        RigidBody() = default;

        RigidBody(float mass, RigidbodyType rbType)
            : mass(mass), type(rbType), shape(shape), scale(scale), position(position)
        {
        };

        RigidBody(float mass, RigidbodyType rbType, CollisionGroups collisionGroup)
            : mass(mass), type(rbType), shape(shape), scale(scale), position(position), collisionGroup(collisionGroup)
        {
        };

        virtual void Serialize(BlobSerializer& serializer) override {};
        virtual void Deserialize(BlobSerializer& serializer)override {};
        virtual bool IsValid()
        {
            return true;
        }

        glm::vec3 position;
        float mass;
        // float friction;
        // float restitution;
        RigidbodyType type;
        RigidBodyShape shape;
        glm::vec3 scale;
        btRigidBody* rbReference;
        CollisionGroups collisionGroup = GROUP_DEFAULT;
        CollisionGroups collisionMask = ALL_GROUPS;
    };


    class PHOENIX_API PhysicsSubsystem
    {
    public:
        PhysicsSubsystem();
        PhysicsSubsystem(float gravity);

        bool HasRigidBody(EntityIdentifier entityId);
        void AddRigidBody(EntityIdentifier, RigidBody rigidBody);
        void SetRigidbodyPosition(EntityIdentifier entityId, glm::vec3 position);
        void SetRigidBodyRotation(EntityIdentifier entityId, float angle, glm::vec3 axis = glm::vec3(1, 0, 0));
        /**
         * \brief SetRigidBodyScale use it carefully as it will need to recreate the rigid body
         * \param entityId 
         * \param scale 
         */
        void SetRigidBodyScale(EntityIdentifier entityId, glm::vec3 scale);
        void DeleteRigidBody(EntityIdentifier entityId);
        void Update();
        HitResult TraceRayCast(glm::vec3 start,glm::vec3 end);
        HitResult TraceRayCast(glm::vec3 start,glm::vec3 end, CollisionGroups collisionGroup , CollisionGroups collisionMask,  DebgugLine debugLine);

    private: 
        btDiscreteDynamicsWorld* m_dynamicsWorld;

        void SetTimeout(std::function<void()> function, int delay);
        std::vector<DebugData> m_debugData;
    };
}

