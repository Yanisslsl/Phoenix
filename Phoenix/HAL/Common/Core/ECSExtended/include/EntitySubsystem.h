#pragma once
#include <string>
#include "ECS/include/ColliderSystem.h"
#include "ECS/include/EntityManager.h"
#include "ECS/include/TransformSystem.h"
#include "Utils/Color.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "ECS/include/SpriteSystem.h"


namespace Phoenix
{

    inline int32_t NODE_WIDTH = 100;
    inline int32_t NODE_HEIGHT = 100;
    struct EntitySubsystem;


    /**
     * \brief Wrapper around the entity creation and destruction.
     *        Use EntityManager and systems to manage the entities.
     */
    class PHOENIX_API EntitySubsystem
    {
    public:
        EntitySubsystem();
        ~EntitySubsystem();
        void Initalize();
        Ref<Entity> CreateEntity(std::string name, bool isStandAlone = true);
        void DestroyEntity(EntityId id);
        Ref<Entity> GetEntityByName(std::string name);
        void BindUpdate(EntityId entityId, std::function<void()> updateFunction);
        void BindOnStart(std::function<void()> onStartFunction);
        void AddTag(EntityId entity, TagType tag);
        void Update();
        void OnStart();
        void DeleteTag(EntityId entity, TagType tag);
        TagType GetTag(EntityId entity);
        Ref<Entity> GetEntityById(EntityId id);
        std::vector<Ref<Entity>> GetEntities();
        std::vector<Ref<Entity>> GetEntitiesByTag(TagType tag);
        bool IsInitialized() { return is_Initialized; }
        void SetIsInitialized(bool value);
    private:
        friend class Entity;
        EntityManager* m_EntityManager;
        TransformSystem* m_TransformSystem;
        bool is_Initialized = false;
        /**
         * \brief Used to initalized entities in their onStartMethod;
         */
        std::vector<std::function<void()>> m_Binded_OnStarts;
    };
}

