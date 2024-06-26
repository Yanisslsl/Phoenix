


#include "ECSExtended/include/TransformSubsytem.h"

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
        Application::Get().GetRegistry().emplace<TransformComponent>(entity, component.position, component.rotation, component.scale, component.rotationAxis);
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

    void TransformSubsytem::SetTransformRotation(EntityIdentifier id, float rotation, glm::vec3 axis)
    {
        Application::Get().GetRegistry().patch<TransformComponent>(id, [&rotation, &axis](TransformComponent& component)
        {
            component.rotation = rotation;
            component.rotationAxis = axis;
        });
    }

    void TransformSubsytem::SetTransformScale(EntityIdentifier entity, glm::vec2 scale)
    {
        Application::Get().GetRegistry().patch<TransformComponent>(entity, [&scale](TransformComponent& component) { component.scale = glm::vec3(scale, 1.0); });
    }

    void TransformSubsytem::SetTransformScale(EntityIdentifier entity, glm::vec3 scale)
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

    glm::vec3 TransformSubsytem::GetTransformRotationAxis(EntityIdentifier id)
    {
        return Application::Get().GetRegistry().get<TransformComponent>(id).rotationAxis;
    }


    glm::vec3 TransformSubsytem::GetTransformScale(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().get<TransformComponent>(entity).scale;
    }
}
