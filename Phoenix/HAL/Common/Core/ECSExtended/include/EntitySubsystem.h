#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "ECS/include/ColliderSystem.h"
#include "ECS/include/EntityComponent.h"
#include "ECS/include/EntityManager.h"
#include "ECS/include/TransformSystem.h"
#include "Utils/Color.h"

namespace Phoenix
{

    inline int32_t NODE_WIDTH = 100;
    inline int32_t NODE_HEIGHT = 100;
    struct EntitySubsystem;
    struct TransformComponent
    {
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    };

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

    
    
    class PHOENIX_API Entity
    {
    public:
        Entity(EntitySubsystem* owner, EntityId id, std::string name)
        : m_id(id)
        , m_name(name)
        , m_owner(owner)
        {
            m_parent = nullptr;
            m_children = std::vector<Ref<Entity>>();
        }
        glm::vec2 GetTransformPosition() const;
        void SetTransformPosition(glm::vec2 position);

        glm::vec2 GetScale() const;
        void SetScale(glm::vec2 scale);
        void SetScale(int scale);

        float GetRotation() const;
        void SetRotation(float rotation);

        std::string GetName(){ return m_name; }

        void AddChild(Ref<Entity> child)
        {
            m_children.push_back(child);
            child->m_parent = this;
            RecomputeModelMatrix();
            UdpateChildsModelMatrix();
        }

        void DeleteChild(Ref<Entity> child)
        {
            for (auto it = m_children.begin(); it != m_children.end(); it++)
            {
                if (*it == child)
                {
                    m_children.erase(it);
                    return;
                }
            }
        }

        glm::mat4 GetRotationMatrix() const;
        glm::mat4 GetScaleMatrix() const;
        glm::mat4 GetTranslationMatrix() const;
        glm::mat4 GetLocalModelMatrix() const;
        glm::mat4 GetWorldModelMatrix() const;

        BoxCollider GetCollider() const;

        void UdpateChildsModelMatrix()
        {
            for (auto& child : m_children)
            {
                child->RecomputeModelMatrix();
                if(!child->m_children.empty())
                {
                    child->UdpateChildsModelMatrix();
                }
            }
        }

        void RecomputeModelMatrix()
        {
            Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
        }
        
        //#TODO change to
        //template <T , typename ...args>
        
        
        template <typename T>
        void AddComponent(T component);

        template <>
        void AddComponent<Phoenix::TransformComponent>(TransformComponent component);

        template <>
        void AddComponent<Phoenix::SpriteComponent>(SpriteComponent component);

        template <>
        void Entity::AddComponent<Phoenix::BoxCollider>(BoxCollider component);
        
        template <typename T>
        void OnComponentUpdated(T component)
        {
            static_assert(sizeof(T) == 0, "Component not found");
        }
    public:
        std::string m_name;
        EntityId m_id;
        EntitySubsystem* m_owner;
    private:
        Entity* m_parent;
        std::vector<Ref<Entity>> m_children;
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
        ColliderSystem* m_ColliderSystem;
    };
}

