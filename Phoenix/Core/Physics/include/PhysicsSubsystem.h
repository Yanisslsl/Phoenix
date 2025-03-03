#pragma once
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

#include "ECSExtended/include/IComponent.h"


class btDiscreteDynamicsWorld;

namespace Phoenix
{

    enum RigidbodyType
    {
        STATIC,
        DYNAMIC
    };

    enum RigidBodyShape
    {
        SPHERE,
        BOX
    };

    
    struct PHOENIX_API RigidBody: IComponent, AutoRegister<RigidBody>
    {
    public:
        RigidBody() = default;
        // RigidBody(float mass, float friction, float restitution, RigidbodyType type, RigidBodyShape shape, glm::vec3 scale, glm::vec3 position)
        //     : mass(mass), friction(friction), restitution(restitution), type(type), shape(shape), scale(scale), position(position)   
        // {
        // };

        RigidBody(float mass, RigidbodyType rbType)
            : mass(mass), type(rbType), shape(shape), scale(scale), position(position)
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
    };
    
    class PhysicsSubsystem
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
    private: 
        btDiscreteDynamicsWorld* m_dynamicsWorld;
    };

    
}

