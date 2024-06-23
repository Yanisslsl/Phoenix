#include "Core/ECSExtended/include/SpriteSubsystem.h"

#include "Core/Application/include/Application.h"

namespace Phoenix
{
    SpriteSubsystem::SpriteSubsystem()
    {
    }

    SpriteSubsystem::~SpriteSubsystem()
    {
    }

    bool SpriteSubsystem::HasSpriteComponent(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().try_get<SpriteComponent>(entity) != nullptr;
    }

    void SpriteSubsystem::AddSpriteComponent(EntityIdentifier entity, SpriteComponent spriteComponent)
    {
        Application::Get().GetRegistry().emplace<SpriteComponent>(entity, spriteComponent);
    }

    SpriteComponent SpriteSubsystem::GetSpriteComponent(EntityIdentifier entity)
    {
        return Application::Get().GetRegistry().get<SpriteComponent>(entity);
    }
}
