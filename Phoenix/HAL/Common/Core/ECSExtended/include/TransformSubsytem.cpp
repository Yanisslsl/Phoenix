#include "TransformSubsytem.h"


namespace Phoenix
{
    TransformSubsytem::TransformSubsytem()
    {
        m_TransformSystem = new TransformSystem(0, 1000);
    }

    TransformSubsytem::~TransformSubsytem()
    {
        delete m_TransformSystem;
    }

    void TransformSubsytem::AddTransformComponent(EntityId id, TransformComponent component)
    {
        m_TransformSystem->AddComponentTo(id);
        m_TransformSystem->SetEntityPostion(id, component.position);
        m_TransformSystem->SetEntityRotation(id, component.rotation);
        m_TransformSystem->SetEntityScale(id, component.scale);
    }

    void TransformSubsytem::SetTransformPosition(EntityId id, glm::vec2 position)
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

    glm::vec2 TransformSubsytem::GetTransformPosition(EntityId id)
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