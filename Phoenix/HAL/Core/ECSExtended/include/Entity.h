// Entity.h

#pragma once
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Tag.h"
#include "Core/Graphics/Render/include/Renderer.h"
#include "Core/Serialization/include/SerializerSubsystem.h"
#include "ECS/include/EntityComponent.h"

namespace Phoenix
{
    class EntitySubsystem;
    struct BoxCollider;
    struct SpriteComponent;
    class TransformComponent;

    struct EntityType
    {
      std::string name;
      bool isStandAlone;
      std::function<void()> updateFunction;
      TagType tag;
    }; 

    class PHOENIX_API IComponent: public ISerializable
    {
    public:
        IComponent() = default;
        virtual void Serialize(BlobSerializer& serializer) = 0;
        virtual void Deserialize(BlobSerializer& serializer) = 0;
    };

    /**
     * \brief Entity class that represent a game object in the game.
     */
    class PHOENIX_API Entity: public ISerializable, public Phoenix::AutoRegister<Entity>
    {
    public:
        Entity()
        {
            
        }
        Entity(EntityIdentifier id, std::string name, TagType tag = 0, bool isStandAlone = true)
        : m_id(id)
        , m_name(name)
        , m_Tag(tag)
        , isStandAlone(isStandAlone)
        {
            m_parent = nullptr;
            m_children = std::vector<Ref<Entity>>();
        }
        
        // FOR WRAPPED MODE ONLY
        void BindUpdate(std::function<void()> updateFunction);
        void Update();
        // FOR WRAPPED MODE ONLY

        /**
         * \brief Get the transform position of the entity
         * \return glm::vec3
         */
        glm::vec3 GetTransformPosition() const;
        
        /**
         * \brief Set the transform position of the entity
         * \param position
         */
        void SetTransformPosition(glm::vec3 position);
        
        /**
         * \brief Destroy the entity
         */
        void Destroy();

        /**
         * \brief Add a tag to the entity
         * \param tag
         */
        void AddTag(TagType tag);

        /**
         * \brief Delete a tag from the entity
         * \param tag
         */
        void DeleteTag(TagType tag);

        /**
         * \brief Check if the entity has a tag
         * \param tag
         * \return bool
         */
        bool HasTag(TagType tag);

        /**
         * \brief Get the scale of the entity
         * \return glm::vec2
         */
        glm::vec2 GetScale() const;

        /**
         * \brief Set the scale of the entity
         * \param scale
         */
        void SetScale(glm::vec2 scale);
        void SetScale(int scale);


        /**
         * \brief Get the rotation of the entity
         * \return float
         */
        float GetRotation() const;

        /**
         * \brief Set the rotation of the entity
         * \param rotation
         */
        void SetRotation(float rotation);


        /**
         * \brief Get the name of the entity
         * \return std::string
         */
        std::string GetName(){ return m_name; }


        /**
         * \brief Add a child to the entity
         */
        void AddChild(Ref<Entity> child)
        {
            m_children.push_back(child);
            child->m_parent = this;
            RecomputeModelMatrix();
            UdpateChildrenModelMatrix();
        }

        /**
         * \brief Delete a child from the entity
         * \param child
         */
        void DeleteChild(Ref<Entity> child)
        {
            for (auto it = m_children.begin(); it != m_children.end(); it++)
            {
                if (*it == child)
                {
                    m_children.erase(it);
                    return;
                }
            }
        }

        /**
         * \brief Get the rotation matrix of the entity
         * \return rotation matrix
         */
        glm::mat4 GetRotationMatrix() const;

        /**
         * \brief Get the scale matrix of the entity
         * \return scale matrix
         */
        glm::mat4 GetScaleMatrix() const;

        /**
         * \brief Get the translation matrix of the entity
         * \return translation matrix
         */
        glm::mat4 GetTranslationMatrix() const;
        
        /**
         * \brief Get the local model matrix of the entity
         * \return local model matrix
         */
        glm::mat4 GetLocalModelMatrix() const;

        /**
         * \brief Get the world model matrix of the entity
         * \return world model matrix
         */
        glm::mat4 GetWorldModelMatrix() const;


        /**
         * \brief Get the sprite component of the entity
         * \return sprite component
         */
        BoxCollider GetCollider() const;

        /**
         * \brief Get the transform component of the entity
         * \return transform component
         */
        TransformComponent GetTransformComponent() const;


        /**
         * \brief Play an animation on the entity
         * \param animationName animation name to play
         * \param onAnimationEnd function to call when the animation ends
         */
        void Play(std::string animationName, std::function<void()> onAnimationEnd = nullptr);

         /**
         * \brief Create an animation on the entity
         * \param name animation name
         * \param paths vector of paths to the textures
         * \param duration duration of the animation
         * \param totalFrames total frames of the animation
         */
        void CreateAnimation(std::string name, std::vector<std::string> paths, float duration, int totalFrames);

        /**
         * \brief Bind a function to the entity update in client code
         * \param updateFunction
         */
        void Update(std::function<void()> updateFunction);


        /**
         * \brief update children model matrix
         */
        void UdpateChildrenModelMatrix()
        {
            for (auto& child : m_children)
            {
                child->RecomputeModelMatrix();
                if(!child->m_children.empty())
                {
                    child->UdpateChildrenModelMatrix();
                }
            }
        }


        /**
         * \brief recompute model matrix
         */
        void RecomputeModelMatrix()
        {
            Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
        }

        /**
         * \brief Add a component to the entity
         * \tparam T
         * \param component
         */
        template <typename T>
        void AddComponent(T component);


        /**
         * \brief Hook called when a component is updated
         * \tparam T
         * \param component
         */
        template <typename T>
        void OnComponentUpdated(T component)
        {
            static_assert(sizeof(T) == 0, "Component not found");
        }

        void Serialize(BlobSerializer& serializer) override;
        void Deserialize(BlobSerializer& serializer) override;
    public:
        std::string m_name;
        EntityIdentifier m_id;
        TagType m_Tag = 0;
        std::function<void()> m_updateFunction;
        bool isStandAlone = false;
    private:
        Entity* m_parent;
        std::vector<Ref<Entity>> m_children;
    private:
         entt::entity m_EntityHandle{entt::null};
    };
}


template<>
void PHOENIX_API Phoenix::Entity::AddComponent<Phoenix::SpriteComponent>(SpriteComponent component);

template<>
void PHOENIX_API Phoenix::Entity::AddComponent<Phoenix::BoxCollider>(BoxCollider component);

template<>
void PHOENIX_API Phoenix::Entity::AddComponent<Phoenix::TransformComponent>(TransformComponent component);
