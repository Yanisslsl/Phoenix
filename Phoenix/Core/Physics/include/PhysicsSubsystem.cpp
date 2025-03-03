#include "PhysicsSubsystem.h"

#include <iostream>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <glm/detail/type_quat.hpp>
#include <LinearMath/btDefaultMotionState.h>
#include "Core/Application/include/Application.h"
#include "ECSExtended/include/Entity.h"


namespace Phoenix
{
    PhysicsSubsystem::PhysicsSubsystem()
    {
        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
        m_dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
        m_dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
        float fixedTimeStep = 1.0f/60.0f;
        m_dynamicsWorld->getSolverInfo().m_timeStep = fixedTimeStep;
        m_dynamicsWorld->getSolverInfo().m_numIterations = 10;
    }

    PhysicsSubsystem::PhysicsSubsystem(float gravity)
    {
        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
        m_dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
        m_dynamicsWorld->setGravity(btVector3(0, gravity, 0));
        float fixedTimeStep = 1.0f/60.0f;
        m_dynamicsWorld->getSolverInfo().m_timeStep = fixedTimeStep;
        m_dynamicsWorld->getSolverInfo().m_numIterations = 10;

    }

    bool PhysicsSubsystem::HasRigidBody(EntityIdentifier entityId)
    {
        return Application::Get().GetRegistry().try_get<RigidBody>(entityId) != nullptr;
    }

    void PhysicsSubsystem::AddRigidBody(EntityIdentifier entityId, RigidBody rigidBody)
    {
        auto shapeType = rigidBody.shape;
        auto scale = rigidBody.scale;
        auto position = rigidBody.position;
        auto rbType = rigidBody.type;
        btCollisionShape* shape = nullptr;
        switch (shapeType)
        {
            case RigidBodyShape::BOX:
                {
                    shape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));
                    btTransform transform;
                    transform.setIdentity();
                    transform.setOrigin(btVector3(position.x, position.y, position.z));
                    btVector3 localInertia(0, 0, 0);
                    if(rigidBody.mass != 0 && rbType == RigidbodyType::STATIC)
                    {
                        PX_WARN("Static rigidbodies should not have mass");
                    }
                    btScalar mass(0.);
                    if(rbType == RigidbodyType::DYNAMIC)
                    {
                        mass = rigidBody.mass;
                        shape->calculateLocalInertia(mass, localInertia);
                    }
                    btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
                    btRigidBody* body = new btRigidBody(mass, myMotionState, shape, localInertia);
                    rigidBody.rbReference = body;
                    Application::Get().GetRegistry().emplace<RigidBody>(entityId, rigidBody);
                    m_dynamicsWorld->addRigidBody(body);
                    break;
                }
            default:
                PX_ERROR("RigidBody shape not supported");
                break;
        }
    }

    void PhysicsSubsystem::SetRigidbodyPosition(EntityIdentifier entityId, glm::vec3 position)
    {
        Application::Get().GetRegistry().patch<RigidBody>(entityId, [position](RigidBody& rb) {
            // Update the component's position field
            rb.position = position;
        
            // Update the actual Bullet rigidbody if it exists
            if (rb.rbReference) {
                // Create a new transform
                btTransform transform;
            
                // Get the current rotation from the rigid body to preserve it
                btTransform currentTransform;
                rb.rbReference->getMotionState()->getWorldTransform(currentTransform);
            
                // Set the new transform with the same rotation but new position
                transform.setOrigin(btVector3(position.x, position.y, position.z));
                transform.setRotation(currentTransform.getRotation());
            
                // Update the motion state with the new transform
                rb.rbReference->getMotionState()->setWorldTransform(transform);
            
                // Update the world transform directly
                rb.rbReference->setWorldTransform(transform);
            
                // Activate the body to ensure physics simulation notices the change
                rb.rbReference->activate(true);
            }
        });
    }

    void PhysicsSubsystem::SetRigidBodyRotation(EntityIdentifier entityId, float angle, glm::vec3 axis)
    {
        Application::Get().GetRegistry().patch<RigidBody>(entityId, [angle, axis](RigidBody& rb) {
            // Update the actual Bullet rigidbody if it exists
            if (rb.rbReference) {
                // Create a new transform
                btTransform transform;
            
                // Get the current position from the rigid body to preserve it
                btTransform currentTransform;
                rb.rbReference->getMotionState()->getWorldTransform(currentTransform);
            
                // Convert angle and axis to btQuaternion
                // Normalize the axis vector
                glm::vec3 normalizedAxis = glm::normalize(axis);
            
                // Create a btQuaternion from angle (in radians) and axis
                btQuaternion btRot(btVector3(normalizedAxis.x, normalizedAxis.y, normalizedAxis.z), angle);
            
                // Set the new transform with the same position but new rotation
                transform.setOrigin(currentTransform.getOrigin());
                transform.setRotation(btRot);
            
                // Update the motion state with the new transform
                rb.rbReference->getMotionState()->setWorldTransform(transform);
            
                // Update the world transform directly
                rb.rbReference->setWorldTransform(transform);
            
                // Activate the body to ensure physics simulation notices the change
                rb.rbReference->activate(true);
            }
        });
    }

    void PhysicsSubsystem::SetRigidBodyScale(EntityIdentifier entityId, glm::vec3 scale)
    {
    Application::Get().GetRegistry().patch<RigidBody>(entityId, [scale, this](RigidBody& rb) {
        // Update the component's scale field
        rb.scale = scale;
        
        // For rigid bodies, changing scale requires recreating the collision shape
        // because Bullet doesn't support direct scaling of collision shapes
        if (rb.rbReference) {
            // Store current position and rotation
            btTransform currentTransform;
            rb.rbReference->getMotionState()->getWorldTransform(currentTransform);
            btVector3 position = currentTransform.getOrigin();
            btQuaternion rotation = currentTransform.getRotation();
            
            // Store current motion properties
            btVector3 linearVelocity = rb.rbReference->getLinearVelocity();
            btVector3 angularVelocity = rb.rbReference->getAngularVelocity();
            
            // Remove the old rigid body from the world
            m_dynamicsWorld->removeRigidBody(rb.rbReference);
            
            // Clean up the old rigid body and its components
            delete rb.rbReference->getMotionState();
            delete rb.rbReference->getCollisionShape();
            delete rb.rbReference;
            
            // Create a new collision shape with the updated scale
            btCollisionShape* collisionShape = nullptr;
            switch (rb.shape) {
                case RigidBodyShape::BOX:
                    collisionShape = new btBoxShape(btVector3(scale.x * 0.5f, scale.y * 0.5f, scale.z * 0.5f));
                    break;
                // Add other shape types as needed
                default:
                    collisionShape = new btBoxShape(btVector3(scale.x * 0.5f, scale.y * 0.5f, scale.z * 0.5f));
                    break;
            }
            
            // Create motion state
            btDefaultMotionState* motionState = new btDefaultMotionState(
                btTransform(rotation, position)
            );
            
            // Setup the rigid body construction info
            btVector3 localInertia(0, 0, 0);
            if (rb.mass != 0.0f) {  // Only calculate inertia for dynamic bodies
                collisionShape->calculateLocalInertia(rb.mass, localInertia);
            }
            
            btRigidBody::btRigidBodyConstructionInfo rbInfo(
                rb.mass, motionState, collisionShape, localInertia
            );
            
            // Create the new rigid body
            rb.rbReference = new btRigidBody(rbInfo);
            
            // Restore motion properties
            rb.rbReference->setLinearVelocity(linearVelocity);
            rb.rbReference->setAngularVelocity(angularVelocity);
            
            // // Set other properties as needed based on the body type
            // if (rb.type == RigidbodyType::STATIC) {
            //     rb.rbReference->setCollisionFlags(rb.rbReference->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
            // } else if (rb.type == RigidbodyType::Kinematic) {
            //     rb.rbReference->setCollisionFlags(rb.rbReference->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
            // }
            
            // Add the new rigid body to the world
            m_dynamicsWorld->addRigidBody(rb.rbReference);
            
            // Activate the body
            rb.rbReference->activate(true);
        }
    });
}

    void PhysicsSubsystem::DeleteRigidBody(EntityIdentifier entityId)
    {
        if(!HasRigidBody(entityId)) return;
        auto rigidBody = Application::Get().GetRegistry().get<RigidBody>(entityId);
        m_dynamicsWorld->removeRigidBody(rigidBody.rbReference);
        Application::Get().GetRegistry().remove<RigidBody>(entityId);
    }

    void PhysicsSubsystem::Update()
    {
        m_dynamicsWorld->stepSimulation(1.0f/60.0f, 1);
        Application::Get().GetRegistry().view<RigidBody>().each([](auto entity, RigidBody& rb)
        {
            auto body = rb.rbReference;
            btTransform trans;
            body->getMotionState()->getWorldTransform(trans);
            Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(entity)->SetTransformPosition(glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
        });
    }
}
