#include "TransformSubsytem.h"


namespace Phoenix
{
    TransformSubsytem::TransformSubsytem()
    {
        m_TransformSystem = new TransformSystem(1, 1000);
    }

    TransformSubsytem::~TransformSubsytem()
    {
        delete m_TransformSystem;
    }

    void TransformSubsytem::AddTransformComponent(EntityId id, TransformComponent component)
    {
        m_TransformSystem->AddComponentTo(id);
        m_TransformSystem->SetEntityId(id);
        m_TransformSystem->SetEntityPostion(id, component.position);
        m_TransformSystem->SetEntityRotation(id, component.rotation);
        m_TransformSystem->SetEntityScale(id, component.scale);
    }

    bool TransformSubsytem::HasTransformComponent(EntityId id)
    {
        return m_TransformSystem->HasTransform(id);
    }

    TransformComponent TransformSubsytem::GetTransformComponent(EntityId id)
    {
        TransformComponent component;
        glm::vec3 position = m_TransformSystem->GetEntityPosition(id);
        float rotation = m_TransformSystem->GetEntityRotation(id);
        glm::vec2 scale = m_TransformSystem->GetEntityScale(id);
        component.position = position;
        component.rotation = rotation;
        component.scale = scale;
        component.entityId = id;
        return component;
    }

    void TransformSubsytem::DeleteTransformComponent(EntityId id)
    {
        m_TransformSystem->DeleteComponent(id);
    }

    void TransformSubsytem::SetTransformPosition(EntityId id, glm::vec3 position)
    {
        m_TransformSystem->SetEntityPostion(id, position);
    }

    void TransformSubsytem::SetTransformRotation(EntityId id, float rotation)
    {
        m_TransformSystem->SetEntityRotation(id, rotation);
    }

    void TransformSubsytem::SetTransformScale(EntityId id, glm::vec2 scale)
    {
        m_TransformSystem->SetEntityScale(id, scale);
    }

    glm::vec3 TransformSubsytem::GetTransformPosition(EntityId id)
    {
        return m_TransformSystem->GetEntityPosition(id);
    }

    float TransformSubsytem::GetTransformRotation(EntityId id)
    {
        return m_TransformSystem->GetEntityRotation(id);
    }

    glm::vec2 TransformSubsytem::GetTransformScale(EntityId id)
    {
        return m_TransformSystem->GetEntityScale(id);
    }
}