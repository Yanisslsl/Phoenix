#pragma once
#include <string>

#include "Core.h"
#include "Entity.h"
#include "ECS/include/EntityComponent.h"
#include "ECS/include/SpriteSystem.h"
#include "Utils/Color.h"

namespace Phoenix
{
    struct SpriteComponent:  IComponent
    {
    public:
        std::string textureFilePath;
        ColorCode colorCode;
        EntityId entityId;
        SpriteComponent() = default;
        SpriteComponent(std::string texturePath)
        {
            textureFilePath = texturePath;
        }
        SpriteComponent(ColorCode color)
        {
            colorCode = color;
        }
        virtual void Serialize(BlobSerializer& serializer) override
        {
            serializer.WriteHeader(SpriteComponentSerializeType);
            serializer.Write(&textureFilePath, sizeof(textureFilePath));
            serializer.Write(&colorCode, sizeof(colorCode));
            serializer.Write(&entityId, sizeof(entityId));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            serializer.Read(&textureFilePath, sizeof(textureFilePath));
            serializer.Read(&colorCode, sizeof(colorCode));
            serializer.Read(&entityId, sizeof(entityId));
        }

        virtual std::string GetStaticType() override
        {
            return "SpriteComponent";
        } 
    };
    
    class PHOENIX_API SpriteSubsystem
    {
    public:
        SpriteSubsystem();
        ~SpriteSubsystem();

        void AddSpriteComponent(EntityId entity, SpriteComponent spriteComponent);
        bool HasSpriteComponent(EntityId entity);
        SpriteComponent GetSpriteComponent(EntityId entity);
    private:
        SpriteSystem* m_SpriteSystem;
    };
}
