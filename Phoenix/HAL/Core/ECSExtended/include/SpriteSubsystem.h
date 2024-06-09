#pragma once
#include <string>
#include "Core.h"
#include "Entity.h"
#include "ECS/include/EntityComponent.h"
#include "ECS/include/SpriteSystem.h"
#include "Utils/Color.h"
#include "Core/Serialization/include/BlobSerializer.h"

namespace Phoenix
{
    /**
     * \brief SpriteComponent class that represent a sprite component in the game.
     */
    struct SpriteComponent:  IComponent,  AutoRegister<SpriteComponent>
    {
        std::string textureFilePath;
        ColorCode colorCode;
        EntityIdentifier entityId;
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
            serializer.WriteString(textureFilePath);
            serializer.Write(&colorCode, sizeof(colorCode));
            serializer.Write(&entityId, sizeof(entityId));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            serializer.ReadString(textureFilePath);
            serializer.Read(&colorCode, sizeof(colorCode));
            serializer.Read(&entityId, sizeof(entityId));
        }
    };

    /**
     * \brief SpriteSubsystem class that represent a sprite subsystem in the game.
     *        Used to manage sprite components in the game.
     */
    class PHOENIX_API SpriteSubsystem
    {
    public:
        SpriteSubsystem();
        ~SpriteSubsystem();

        /**
         * \brief Add a sprite component to the entity
         * \param entity EntityId to add
         * \param spriteComponent SpriteComponent to add
         */
        void AddSpriteComponent(EntityIdentifier entity, SpriteComponent spriteComponent);

        /**
         * \brief Get whether the entity has a sprite component
         * \param entity EntityId  to check
         * \return if entity has sprite component
         */
        bool HasSpriteComponent(EntityIdentifier entity);
        SpriteComponent GetSpriteComponent(EntityIdentifier entity);
    private:
        SpriteSystem* m_SpriteSystem;
    };
}
