#include "../include/EntitySubsystem.h"

#include "Windows/Core/Application/include/Application.h"


namespace Phoenix
{

    EntitySubsystem::EntitySubsystem()
    {
        m_EntityManager = new EntityManager();
        m_TransformSystem = new TransformSystem(0, 1000);
        m_ColliderSystem = new ColliderSystem(1, 1000);
    }
    
    Ref<Entity> EntitySubsystem::CreateEntity(std::string name)
    {
        EntityId entityId = m_EntityManager->Create(name);
        return CreateRef<Entity>(Entity{ this, entityId,   name });
    }

    void EntitySubsystem::DestroyEntity(Entity entity)
    {
        m_EntityManager->Remove(entity.m_id);
    }

    Ref<Entity> EntitySubsystem::GetEntity(std::string name)
    {
        EntityId entityId  = m_EntityManager->GetEntity(name);
        return CreateRef<Entity>(Entity{ this, entityId, name });
    }

    std::vector<Ref<Entity>> EntitySubsystem::GetEntities()
    {
        std::vector<Ref<Entity>> entities;
        for (auto& entityName : m_EntityManager->GetEntitiesName())
        {
            auto entity = m_EntityManager->GetEntity(entityName);
            entities.push_back(CreateRef<Entity>(Entity{ this, entity, entityName }));
        }
        return entities;
    }

    template<typename T>
    void Entity::AddComponent(T component)
    {
        static_assert(sizeof(T) == 0, "Component not found");
    }

template<>
void Entity::OnComponentUpdated<Phoenix::TransformComponent>(Phoenix::TransformComponent component)
{
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
}

template <>
void Entity::AddComponent<Phoenix::TransformComponent>(TransformComponent component)
{
    m_owner->m_TransformSystem->AddComponentTo(m_id);
    m_owner->m_TransformSystem->SetEntityPostion(m_id, component.position);
    m_owner->m_TransformSystem->SetEntityRotation(m_id, component.rotation);
    m_owner->m_TransformSystem->SetEntityScale(m_id, component.scale);
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
    m_owner->m_ColliderSystem->AddComponentTo(m_id);
    m_owner->m_ColliderSystem->SetColliderType(m_id, component.type);
    m_owner->m_ColliderSystem->SetColliderCoordinates(m_id, {component.position, component.width, component.height});
    m_owner->m_ColliderSystem->SetOnHitCallback(m_id, component.OnHit);
    component.position = GetTransformPosition();
    Application::Get().GetSubSystem<CollisionSubSytem>()->Insert((component));
}


glm::vec2 Entity::GetTransformPosition() const
{
    return m_owner->m_TransformSystem->GetEntityPosition(m_id);
}

void Entity::SetTransformPosition(glm::vec2 position)
{
    m_owner->m_TransformSystem->SetEntityPostion(m_id, position);
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
    Application::Get().GetSubSystem<CollisionSubSytem>()->Update(GetCollider());
}

float Entity::GetRotation() const
{
    return m_owner->m_TransformSystem->GetEntityRotation(m_id);
}

void Entity::SetRotation(float rotation)
{
    m_owner->m_TransformSystem->SetEntityRotation(m_id, rotation);
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
}

glm::vec2 Entity::GetScale() const
{
    return m_owner->m_TransformSystem->GetEntityScale(m_id);
}
void Entity::SetScale(glm::vec2 scale)
{
    m_owner->m_TransformSystem->SetEntityScale(m_id, scale);
    Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
}

void Entity::SetScale(int scale)
{
    const glm::vec2 scaleVec = glm::vec2((float)scale, (float)scale);
    m_owner->m_TransformSystem->SetEntityScale(m_id, scaleVec);
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
    const auto rotation = m_owner->m_TransformSystem->GetEntityRotation(m_id);
    return glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 Entity::GetScaleMatrix() const
{
    const auto scale = m_owner->m_TransformSystem->GetEntityScale(m_id);
    return glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
}

// Only take parent translation into account for computing the child position
glm::mat4 Entity::GetTranslationMatrix() const
{
    const auto transform = m_owner->m_TransformSystem->GetEntityPosition(m_id);
    if(m_parent)
    {
        return m_parent->GetTranslationMatrix() * translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, 1.0f));
    }
    return translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, 1.0f));
}

BoxCollider Entity::GetCollider() const
{
    auto colliderType =  m_owner->m_ColliderSystem->GetColliderType(m_id);
    auto colliderCoordinates = m_owner->m_ColliderSystem->GetColliderCoordinates(m_id);
    auto callback = m_owner->m_ColliderSystem->GetOnHitCallback(m_id);
    auto boxCollider = BoxCollider{colliderType, callback, CollisionShape::RECTANGLE, colliderCoordinates.width, colliderCoordinates.height};
    boxCollider.position = GetTransformPosition();
    return boxCollider;
}



}
