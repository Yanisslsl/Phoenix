#pragma once
#include <entt/entt.hpp>

#include "Tag.h"
#include "Base/Base.h"


namespace Phoenix
{
 class Entity;

 /**
     * \brief Wrapper around the entity creation and destruction.
     *        Use EntityManager and systems to manage the entities.
     */
    class PHOENIX_API EntitySubsystem
    {
    public:
        EntitySubsystem();
        ~EntitySubsystem();
        /**
         * \brief Initialize EntitySubsystem, calls internally OnStart method
         */
        void Initalize();

        /**
         * \brief Create Entity
         * \param name 
         * \param isStandAlone 
         * \return 
         */
        Ref<Entity> CreateEntity(std::string name, bool isStandAlone = true);

        /**
         * \brief Destroy Entity
         * \param id 
         */
        void DestroyEntity(EntityIdentifier id);

        /**
         * \brief Get Entity by name
         * \param name name of entity
         * \return Ref of Entity
         */
        Ref<Entity> GetEntityByName(std::string name);

        /**
         * \brief Bind entity update function to any method
         * \param entityId 
         * \param updateFunction 
         */
        void BindUpdate(EntityIdentifier entityId, std::function<void()> updateFunction);

        /**
         * \brief Bind onStart function to any method
         * \param onStartFunction 
         */
        void BindOnStart(std::function<void()> onStartFunction);

        /**
         * \brief Add tag to entity 
         * \param entity entityId of entity
         * \param tag Tag to add
         */
        void AddTag(EntityIdentifier entity, TagType tag);

        /**
         * \brief Delete tag from entity
         * \param entity EntityId of entity
         * \param tag tag to delete
         */
        void DeleteTag(EntityIdentifier entity, TagType tag);

        /**
         * \brief Get tag of entity
         * \param entity EntityId of entity
         * \return TagType
         */
        TagType GetTag(EntityIdentifier entity);

         /**
         * \brief Update all entities, and call bound update functions
         */
        void Update();

         /**
         * \brief Call onStart functions of entities, and call bound onStart functions
         */
        void OnStart();

         /**
         * \brief Get entity by id
         * \param id EntityIdentifier
         * \return Ref of Entity
         */
        Ref<Entity> GetEntityById(EntityIdentifier id);

        /**
         * \brief Get all entities
         * \return vector of Ref of Entity
         */
        std::vector<Ref<Entity>> GetEntities();

         /**
         * \brief Get all entities by tag
         * \param tag TagType of tag
         * \return vector of Ref of Entity
         */
        std::vector<Ref<Entity>> GetEntitiesByTag(TagType tag);

        /**
         * \brief Get if EntitySubsystem is initialized
         * \return is_Initialized
         */
        bool IsInitialized() { return is_Initialized; }

         /**
         * \brief Set EntitySubsystem initialized, call onStart method if value is true
         * \param value is_Initialized value
         */
        void SetIsInitialized(bool value);
    private:
        friend class Entity;
        bool is_Initialized = false;
        /**
         * \brief Used to initialized entities in their onStartMethod;
         */
        struct BindedOnStart
        {
            bool isCalled = false;
            std::function<void()> onStartFunction;
        };
        std::vector<BindedOnStart> m_Binded_OnStarts;
        std::map<EntityIdentifier, std::function<void()>> m_updateFunctions;
    };
}

