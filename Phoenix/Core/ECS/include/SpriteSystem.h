#pragma once
#include "ComponentSystem.h"
#include "Core.h"
#include "SpriteData.h"

namespace Phoenix
{
    /**
     * @brief SpriteSystem class
     *        SpriteSystem class is a class that holds the data for the sprite component
     */
    class PHOENIX_API SpriteSystem final: public ComponentSystem
    {
    public:
        void InitComponents() override;
        void StartComponents() override;
        void UpdateComponents() override;

        SpriteSystem(ComponentSystemId id, size_t dataSize);
        ~SpriteSystem() override;

        virtual void Init() override;
        virtual void Start() override;
        virtual void Update() override;

        EntityId GetEntityId(EntityId entity);
        void SetEntityId(EntityId entity);

        bool HasSprite(EntityId entity);

        void SetTexturePath(EntityId entity, std::string path);
        std::string GetTexturePath(EntityId entity);

        void SetColor(EntityId entity, ColorCode color);
        ColorCode GetColor(EntityId entity);

    private:
        SpriteData* m_SpriteData;
    };
}
