#pragma once
#include <string>
#include "Core.h"
#include "IComponent.h"
#include "Base/Base.h"
#include "Utils/Color.h"

namespace Phoenix
{

    enum SpriteType
    {
        /**
         * \brief For 2D use cases
         */
        Quad,
        Circle,
        Triangle,

        /**
         * \brief For 3D use cases
         */
        Cube,
        Sphere,
        Pyramid,
        Model
    };
    /**
     * \brief SpriteComponent class that represent a sprite component in the game. Now for 2D use cases.
     */
    struct SpriteComponent: IComponent, AutoRegister<SpriteComponent>
    {
        std::string textureFilePath;
        ColorCode colorCode = Color::NONE;
        SpriteType spriteType;
        SpriteComponent() = default;
        SpriteComponent(std::string texturePath, SpriteType type)
        {
            spriteType = type;
            textureFilePath = texturePath;
        }
        SpriteComponent(ColorCode color,  SpriteType type)
        {
            spriteType = type;
            colorCode = color;
        }
        virtual void Serialize(BlobSerializer& serializer) override
        {
            // serializer.WriteHeader(SpriteComponentSerializeType);
            // serializer.WriteString(textureFilePath);
            // serializer.Write(&colorCode, sizeof(colorCode));
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            // serializer.ReadString(textureFilePath);
            // serializer.Read(&colorCode, sizeof(colorCode));
        }

        virtual bool IsValid() override
        {
            if(textureFilePath.empty() || colorCode == Color::NONE)
            {
                return false;
            }
            return true;
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
    };
}
