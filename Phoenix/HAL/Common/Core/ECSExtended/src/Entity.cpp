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
        auto position = GetTransformPosition();
        component.position = position;
        Application::Get().GetSubSystem<CollisionSubSytem>()->AddCollider(m_id, component);
    }

    glm::vec3 Entity::GetTransformPosition() const
    {
        return Application::Get().GetSubSystem<TransformSubsytem>()->GetTransformPosition(m_id);
    }

    void Entity::SetTransformPosition(glm::vec3 position)
    {
        Application::Get().GetSubSystem<TransformSubsytem>()->SetTransformPosition(m_id, position);
        Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
        if(!Application::Get().GetSubSystem<CollisionSubSytem>()->HasCollider(m_id)) return;
        Application::Get().GetSubSystem<CollisionSubSytem>()->Update(m_id, position);
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

    void Entity::Destroy()
    {
        Application::Get().GetSubSystem<EntitySubsystem>()->DestroyEntity(m_id);
        Application::Get().GetSubSystem<TransformSubsytem>()->DeleteTransformComponent(m_id);
        Application::Get().GetSubSystem<CollisionSubSytem>()->DeleteCollider(m_id);
        Renderer::DeleteShape(m_name);
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
            return m_parent->GetTranslationMatrix() * translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, transform.z));
        }
        return translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, transform.z));
    }

    BoxCollider Entity::GetCollider() const
    {
       return Application::Get().GetSubSystem<CollisionSubSytem>()->GetCollider(m_id);
    }

    void Entity::AddTag(TagType tag)
    {
        TagType entityTag =  Tags::AddTag(tag, m_Tag);
        Application::Get().GetSubSystem<EntitySubsystem>()->AddTag(m_id, entityTag);
    }

    void Entity::DeleteTag(TagType tag)
    {
        TagType entityTag = Tags::RemoveTag(tag, m_Tag);
        Application::Get().GetSubSystem<EntitySubsystem>()->DeleteTag(m_id, entityTag);
    }

    bool Entity::HasTag(TagType tag)
    {
        return Tags::HasTag(tag, m_Tag);
    }

    void Entity::BindUpdate(std::function<void()> updateFunction)
    {
        m_updateFunction = updateFunction;
        Application::Get().GetSubSystem<EntitySubsystem>()->BindUpdate(m_id, updateFunction);
    }

    void Entity::Update()
    {
        if(m_updateFunction)
        {
            m_updateFunction();
        }
    }
}
