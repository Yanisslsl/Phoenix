#pragma once
#include <string>
#include <glm/detail/type_vec2.hpp>

#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "ECS/include/ColliderSystem.h"
#include "ECS/include/EntityManager.h"
#include "ECS/include/TransformSystem.h"
#include "Utils/Color.h"
#include "Common/Core/ECSExtended/include/Entity.h"


namespace Phoenix
{

    inline int32_t NODE_WIDTH = 100;
    inline int32_t NODE_HEIGHT = 100;
    struct EntitySubsystem;


    struct SpriteComponent
    {
        std::string textureFilePath;
        ColorCode colorCode;
        SpriteComponent(std::string texturePath)
        {
            textureFilePath = texturePath;
        }
        SpriteComponent(ColorCode color)
        {
            colorCode = color;
        }
    };
    
    
    struct BoxCollider
    {
    public:
        BoxCollider(CollisionType type, std::function<void(void*)> onHit, CollisionShape shape, float width, float height)
        : type(type), OnHit(onHit), shape(shape), width(width), height(height)
        {
            position = glm::vec2(0, 0);
        }
        CollisionType type;
        glm::vec2 position;
        std::function<void(void*)> OnHit;
        CollisionShape shape;
        float width;
        float height;
      
        //@TODO: create base collider class when adding more colliders types
        bool CollidesWith(void* other)
        {
            switch (shape)
            {
            case CollisionShape::RECTANGLE:
                {
                    const auto otherCollider = *(static_cast<BoxCollider*>(other));
                    if (otherCollider.shape == CollisionShape::RECTANGLE)
                    {
                      if(abs(position.x - otherCollider.position.x) < (width + otherCollider.width) / 2 ){
                          return false;
                      }
                        if(abs(position.y - otherCollider.position.y) < (height + otherCollider.height) / 2 ){
                            return false;
                        }
                        return true;
                    }
                }
            default:
                PX_CORE_ASSERT(false, "Collision shape not supported");
            }
        }
    };

    /**
     * \brief Wrapper around the entity creation and destruction.
     *        Use EntityManager and systems to manage the entities.
     */
    class PHOENIX_API EntitySubsystem
    {
    public:
        EntitySubsystem();
        Ref<Entity> CreateEntity(std::string name);
        void DestroyEntity(Entity entity);
        Ref<Entity> GetEntity(std::string name);
        std::vector<Ref<Entity>> GetEntities();
    private:
        friend class Entity;
        EntityManager* m_EntityManager;
        TransformSystem* m_TransformSystem;
    };
}

