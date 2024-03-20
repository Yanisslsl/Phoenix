#pragma once
#include <string>
#include "ECS/include/ColliderSystem.h"
#include "ECS/include/EntityManager.h"
#include "ECS/include/TransformSystem.h"
#include "Utils/Color.h"
#include "Common/Core/ECSExtended/include/Entity.h"


namespace Phoenix
{

    inline int32_t NODE_WIDTH = 100;
    inline int32_t NODE_HEIGHT = 100;
    struct EntitySubsystem;


    struct SpriteComponent:  public IComponent
    {
        std::string textureFilePath;
        ColorCode colorCode;
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
            
        }
        virtual void Deserialize(BlobSerializer& serializer) override
        {
            
        }
    };
    

    /**
     * \brief Wrapper around the entity creation and destruction.
     *        Use EntityManager and systems to manage the entities.
     */
    class PHOENIX_API EntitySubsystem
    {
    public:
        EntitySubsystem();
        ~EntitySubsystem();
        Ref<Entity> CreateEntity(std::string name);
        void DestroyEntity(EntityId id);
        Ref<Entity> GetEntityByName(std::string name);
        void BindUpdate(EntityId entityId, std::function<void()> updateFunction);
        void AddTag(EntityId entity, TagType tag);
        void Update();
        void DeleteTag(EntityId entity, TagType tag);
        TagType GetTag(EntityId entity);
        Ref<Entity> GetEntityById(EntityId id);
        std::vector<Ref<Entity>> GetEntities();
        std::vector<Ref<Entity>> GetEntitiesByTag(TagType tag);
    private:
        friend class Entity;
        EntityManager* m_EntityManager;
        TransformSystem* m_TransformSystem;
    };
}

