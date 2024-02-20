#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <glm/detail/type_vec2.hpp>

#include "../../Core/ECS/include/EntityManager.h"
#include "../../Core/ECS/include/TransformSystem.h"

#include "../../../Core/Core.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"

namespace Phoenix
{
    struct EntitySubsystem;
    
    struct TransformComponent
    {
        glm::vec2 position;
        glm::vec2 rotation;
        glm::vec2 scale;
    };

    struct SpriteComponent
    {
        std::string texturePath;
    };
    
    class PHOENIX_API Entity
    {
    public:
        Entity(EntitySubsystem* owner, EntityId id, std::string name)
        : m_id(id)
        , m_name(name)
        , m_owner(owner)
        {}

        void SetTransformPosition(glm::vec2 position);

        template <typename T>
        void AddComponent(T component)
        {
            // maybe to restrictful
            static_assert(sizeof(T) == 0, "Component not found");
        }

        template <typename T>
        void OnComponentAdded(T component)
        {
            static_assert(sizeof(T) == 0, "Component not found");
        }

      
    public:
        std::string m_name;
        EntityId m_id;
        EntitySubsystem* m_owner;
    };

    
    /**
     * \brief Wrapper around the entity creation and destruction.
     *        Use EntityManager and systems to manage the entities.
     */
    class PHOENIX_API EntitySubsystem
    {
    public:
        EntitySubsystem();
        Entity* CreateEntity(std::string name);
        void DestroyEntity(Entity entity);
    private:
        friend class Entity;
        EntityManager* m_EntityManager;
        TransformSystem* m_TransformSystem;
    };
}

template<>
inline void Phoenix::Entity::OnComponentAdded<Phoenix::TransformComponent>(Phoenix::TransformComponent component)
{
    Renderer::UpdateShapeTransform(m_name, component.position);
}

template <>
inline void Phoenix::Entity::AddComponent<Phoenix::TransformComponent>(TransformComponent component)
{
    m_owner->m_TransformSystem->AddComponentTo(m_id);
    m_owner->m_TransformSystem->SetEntityPostion(m_id, component.position);
    OnComponentAdded<TransformComponent>(component);
}

template <>
inline void Phoenix::Entity::AddComponent<Phoenix::SpriteComponent>(SpriteComponent component)
{
    Renderer::CreateQuad(m_name, component.texturePath.c_str(), glm::vec2(0.0f));
}

inline void Phoenix::Entity::SetTransformPosition(glm::vec2 position)
{
    m_owner->m_TransformSystem->SetEntityPostion(m_id, position);
    Renderer::UpdateShapeTransform(m_name, position);
}


