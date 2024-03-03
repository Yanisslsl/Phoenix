#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "ECS/include/EntityComponent.h"
#include "ECS/include/EntityManager.h"
#include "ECS/include/TransformSystem.h"
#include "Utils/Color.h"

namespace Phoenix
{
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

        template <typename T>
        void AddComponent(T component)
        {
            static_assert(sizeof(T) == 0, "Component not found");
        }

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
        // @TODO: this should not be neccessary with the ECS data oriented design
        // But for simplicity we will keep it for now to map the entity name to the entity id
    };
}

template<>
inline void Phoenix::Entity::OnComponentUpdated<Phoenix::TransformComponent>(Phoenix::TransformComponent component)
{
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
}

template <>
inline void Phoenix::Entity::AddComponent<Phoenix::TransformComponent>(TransformComponent component)
{
    m_owner->m_TransformSystem->AddComponentTo(m_id);
    m_owner->m_TransformSystem->SetEntityPostion(m_id, component.position);
    m_owner->m_TransformSystem->SetEntityRotation(m_id, component.rotation);
    m_owner->m_TransformSystem->SetEntityScale(m_id, component.scale);
    OnComponentUpdated<TransformComponent>(component);
}

template <>
inline void Phoenix::Entity::AddComponent<Phoenix::SpriteComponent>(SpriteComponent component)
{
    if(component.textureFilePath.empty())
    {
        Renderer::CreateQuad(m_name, Colors::GetColor(component.colorCode),glm::mat4(1));
    } else if(!component.textureFilePath.empty())
    {
        Renderer::CreateQuad(m_name, component.textureFilePath.c_str(), glm::mat4(1));
    } else
    {
        PX_CORE_ASSERT(false, "Sprite is not properly initialized");
    }
}


inline glm::vec2 Phoenix::Entity::GetTransformPosition() const
{
    return m_owner->m_TransformSystem->GetEntityPosition(m_id);
}

inline void Phoenix::Entity::SetTransformPosition(glm::vec2 position)
{
    m_owner->m_TransformSystem->SetEntityPostion(m_id, position);
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
}

inline float Phoenix::Entity::GetRotation() const
{
    return m_owner->m_TransformSystem->GetEntityRotation(m_id);
}

inline void Phoenix::Entity::SetRotation(float rotation)
{
    m_owner->m_TransformSystem->SetEntityRotation(m_id, rotation);
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
}

inline glm::vec2 Phoenix::Entity::GetScale() const
{
    return m_owner->m_TransformSystem->GetEntityScale(m_id);
}
inline void Phoenix::Entity::SetScale(glm::vec2 scale)
{
    m_owner->m_TransformSystem->SetEntityScale(m_id, scale);
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
}

inline void Phoenix::Entity::SetScale(int scale)
{
    const glm::vec2 scaleVec = glm::vec2((float)scale, (float)scale);
    m_owner->m_TransformSystem->SetEntityScale(m_id, scaleVec);
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
}

inline glm::mat4 Phoenix::Entity::GetLocalModelMatrix() const
{
    return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}

inline glm::mat4 Phoenix::Entity::GetWorldModelMatrix() const
{
    return GetLocalModelMatrix();
}
inline glm::mat4 Phoenix::Entity::GetRotationMatrix() const
{
    const auto rotation = m_owner->m_TransformSystem->GetEntityRotation(m_id);
    return glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
}

inline glm::mat4 Phoenix::Entity::GetScaleMatrix() const
{
    const auto scale = m_owner->m_TransformSystem->GetEntityScale(m_id);
    return glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
}

// Only take parent translation into account for computing the child position
inline glm::mat4 Phoenix::Entity::GetTranslationMatrix() const
{
    const auto transform = m_owner->m_TransformSystem->GetEntityPosition(m_id);
    if(m_parent)
    {
        return m_parent->GetTranslationMatrix() * translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, 1.0f));
    }
    return translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, 1.0f));
}

