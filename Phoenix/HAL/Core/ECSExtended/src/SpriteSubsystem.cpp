#include "Core/ECSExtended/include/SpriteSubsystem.h"

namespace Phoenix
{
    SpriteSubsystem::SpriteSubsystem()
    {
        m_SpriteSystem = new SpriteSystem(0, 1000);
    }

    SpriteSubsystem::~SpriteSubsystem()
    {
        delete m_SpriteSystem;
    }

    bool SpriteSubsystem::HasSpriteComponent(EntityId entity)
    {
        return m_SpriteSystem->HasSprite(entity);
    }

    void SpriteSubsystem::AddSpriteComponent(EntityId entity, SpriteComponent spriteComponent)
    {
        m_SpriteSystem->AddComponentTo(entity);
        m_SpriteSystem->SetEntityId(entity);
        if(spriteComponent.textureFilePath.empty())
        {
            m_SpriteSystem->SetColor(entity, spriteComponent.colorCode);
        }
        else
        {
            m_SpriteSystem->SetTexturePath(entity, spriteComponent.textureFilePath);
        }
    }

    SpriteComponent SpriteSubsystem::GetSpriteComponent(EntityId entity)
    {
        SpriteComponent spriteComponent;
        ColorCode color = m_SpriteSystem->GetColor(entity);
        EntityId id = m_SpriteSystem->GetEntityId(entity);
        std::string texturePath = m_SpriteSystem->GetTexturePath(entity);
        spriteComponent.entityId = id;
        if(texturePath.empty())
        {
            spriteComponent.colorCode = color;
        } else
        {
            spriteComponent.textureFilePath = texturePath;
        }
        return spriteComponent;
    }
}
