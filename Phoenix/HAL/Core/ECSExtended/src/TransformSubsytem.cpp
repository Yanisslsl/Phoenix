

#include "Core/ECSExtended/include/TransformSubsytem.h"

#include "Core/Application/include/Application.h"

namespace Phoenix
{
    TransformSubsytem::TransformSubsytem()
    {
    }

    TransformSubsytem::~TransformSubsytem()
    {
    }

    void TransformSubsytem::AddTransformComponent(EntityIdentifier entity, TransformComponent component)
    {
        Application::Get().GetRegistry().emplace<TransformComponent>(entity, component.position, component.rotation, component.scale);
    }

    bool TransformSubsytem::HasTransformComponent(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().try_get<TransformComponent>(entity) != nullptr;
    }

    TransformComponent TransformSubsytem::GetTransformComponent(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().get<TransformComponent>(entity);
    }

    void TransformSubsytem::DeleteTransformComponent(EntityIdentifier entity)
    {
        Application::Get().GetRegistry().remove<TransformComponent>(entity);
    }

    void TransformSubsytem::SetTransformPosition(EntityIdentifier entity, glm::vec3 position)
    {
        Application::Get().GetRegistry().patch<TransformComponent>(entity, [&position](TransformComponent& component) { component.position = position; });
    }

    void TransformSubsytem::SetTransformRotation(EntityIdentifier entity, float rotation)
    {
        Application::Get().GetRegistry().patch<TransformComponent>(entity, [&rotation](TransformComponent& component) { component.rotation = rotation; });
    }

    void TransformSubsytem::SetTransformScale(EntityIdentifier entity, glm::vec2 scale)
    {
        Application::Get().GetRegistry().patch<TransformComponent>(entity, [&scale](TransformComponent& component) { component.scale = scale; });
    }

    glm::vec3 TransformSubsytem::GetTransformPosition(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().get<TransformComponent>(entity).position;
    }

    float TransformSubsytem::GetTransformRotation(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().get<TransformComponent>(entity).rotation;
    }

    glm::vec2 TransformSubsytem::GetTransformScale(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().get<TransformComponent>(entity).scale;
    }
}
