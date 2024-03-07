#include "../include/Entity.h"

#include "Windows/Core/Application/include/Application.h"

namespace Phoenix
{
    template<typename T>
    void Entity::AddComponent(T component)
    {
        static_assert(sizeof(T) == 0, "Component not found");
    }

    template<>
    void Entity::OnComponentUpdated<Phoenix::TransformComponent>(TransformComponent component)
    {
        Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
    }

    template <>
    void Entity::AddComponent<TransformComponent>(TransformComponent component)
    {
        Application::Get().GetSubSystem<TransformSubsytem>()->AddTransformComponent(m_id, component);
        OnComponentUpdated<TransformComponent>(component);
    }

    template <>
    void Entity::AddComponent<Phoenix::SpriteComponent>(SpriteComponent component)
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

    template <>
    void Entity::AddComponent<Phoenix::BoxCollider>(BoxCollider component)
    {
        // m_owner->m_ColliderSystem->AddComponentTo(m_id);
        // m_owner->m_ColliderSystem->SetColliderType(m_id, component.type);
        // m_owner->m_ColliderSystem->SetColliderCoordinates(m_id, {component.position, component.width, component.height});
        // m_owner->m_ColliderSystem->SetOnHitCallback(m_id, component.OnHit);
        // component.position = GetTransformPosition();
        Application::Get().GetSubSystem<CollisionSubSytem>()->AddCollider(m_id, component);
    }


    glm::vec2 Entity::GetTransformPosition() const
    {
        return Application::Get().GetSubSystem<TransformSubsytem>()->GetTransformPosition(m_id);
    }

    void Entity::SetTransformPosition(glm::vec2 position)
    {
        Application::Get().GetSubSystem<TransformSubsytem>()->SetTransformPosition(m_id, position);
        Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
        // Application::Get().GetSubSystem<CollisionSubSytem>()->Update(GetCollider());
    }

    float Entity::GetRotation() const
    {
        return Application::Get().GetSubSystem<TransformSubsytem>()->GetTransformRotation(m_id);
    }

    void Entity::SetRotation(float rotation)
    {
        Application::Get().GetSubSystem<TransformSubsytem>()->SetTransformRotation(m_id, rotation);
        Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
    }

    glm::vec2 Entity::GetScale() const
    {
        return Application::Get().GetSubSystem<TransformSubsytem>()->GetTransformScale(m_id);
    }
    void Entity::SetScale(glm::vec2 scale)
    {
        Application::Get().GetSubSystem<TransformSubsytem>()->SetTransformScale(m_id, scale);
        Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
    }

    void Entity::SetScale(int scale)
    {
        const glm::vec2 scaleVec = glm::vec2((float)scale, (float)scale);
        Application::Get().GetSubSystem<TransformSubsytem>()->SetTransformScale(m_id, scaleVec);
        Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
    }

    glm::mat4 Entity::GetLocalModelMatrix() const
    {
        return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
    }

    glm::mat4 Entity::GetWorldModelMatrix() const
    {
        return GetLocalModelMatrix();
    }
    glm::mat4 Entity::GetRotationMatrix() const
    {
        const auto rotation = Application::Get().GetSubSystem<TransformSubsytem>()->GetTransformRotation(m_id);
        return glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    glm::mat4 Entity::GetScaleMatrix() const
    {
        const auto scale = Application::Get().GetSubSystem<TransformSubsytem>()->GetTransformScale(m_id);
        return glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
    }

    // Only take parent translation into account for computing the child position
    glm::mat4 Entity::GetTranslationMatrix() const
    {
        const auto transform = Application::Get().GetSubSystem<TransformSubsytem>()->GetTransformPosition(m_id);
        if(m_parent)
        {
            return m_parent->GetTranslationMatrix() * translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, 1.0f));
        }
        return translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, 1.0f));
    }

    BoxCollider Entity::GetCollider() const
    {
       return Application::Get().GetSubSystem<CollisionSubSytem>()->GetCollider(m_id);
    }
}
