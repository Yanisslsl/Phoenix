#pragma once
#include <string>
#include <glm/detail/type_vec2.hpp>

#include "Common/Core/Graphics/Render/include/Renderer.h"
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


    struct SpriteComponent
    {
        std::string textureFilePath;
        ColorCode colorCode;
        SpriteComponent(std::string texturePath)
        {
            textureFilePath = texturePath;
        }
        SpriteComponent(ColorCode color)
        {
            colorCode = color;
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
        Ref<Entity> CreateEntity(std::string name);
        void DestroyEntity(Entity entity);
        Ref<Entity> GetEntityByName(std::string name);
        Ref<Entity> GetEntityById(EntityId id);
        std::vector<Ref<Entity>> GetEntities();
    private:
        friend class Entity;
        EntityManager* m_EntityManager;
        TransformSystem* m_TransformSystem;
    };
}

