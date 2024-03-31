// Entity.h

#pragma once
#include "Tag.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "ECS/include/EntityComponent.h"
#include "Common/Core/Serialization/include/BlobSerializer.h"
#include "Common/Core/Serialization/include/SerializerSubsystem.h"

namespace Phoenix
{
    class EntitySubsystem;
    class BoxCollider;
    class SpriteComponent;
    class TransformComponent;

    class PHOENIX_API IComponent: public ISerializable
    {
    public:
        IComponent() = default;
        virtual void Serialize(BlobSerializer& serializer) = 0;
        virtual void Deserialize(BlobSerializer& serializer) = 0;
    };
    
    class PHOENIX_API Entity: public ISerializable, public Phoenix::AutoRegister<Entity>
    {
    public:
        Entity()
        {
            
        }
        Entity(EntityId id, std::string name, TagType tag = 0, bool isStandAlone = true)
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
        
        glm::vec3 GetTransformPosition() const;
        void SetTransformPosition(glm::vec3 position);
        void Destroy();

        void AddTag(TagType tag);
        void DeleteTag(TagType tag);
        bool HasTag(TagType tag);

        glm::vec2 GetScale() const;
        void SetScale(glm::vec2 scale);
        void SetScale(int scale);

        float GetRotation() const;
        void SetRotation(float rotation);

        std::string GetName(){ return m_name; }

        void AddChild(Ref<Entity> child)
        {
            m_children.push_back(child);
            child->m_parent = this;
            RecomputeModelMatrix();
            UdpateChildsModelMatrix();
        }

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

        glm::mat4 GetRotationMatrix() const;
        glm::mat4 GetScaleMatrix() const;
        glm::mat4 GetTranslationMatrix() const;
        glm::mat4 GetLocalModelMatrix() const;
        glm::mat4 GetWorldModelMatrix() const;

        BoxCollider GetCollider() const;
        TransformComponent GetTransformComponent() const;

        void Play(std::string animationName, std::function<void()> onAnimationEnd = nullptr);
        void CreateAnimation(std::string name, std::vector<std::string> paths, float duration, int totalFrames);

        /**
         * \brief Bind a function to the entity update in client code
         * \param updateFunction
         */
        void Update(std::function<void()> updateFunction);

        void UdpateChildsModelMatrix()
        {
            for (auto& child : m_children)
            {
                child->RecomputeModelMatrix();
                if(!child->m_children.empty())
                {
                    child->UdpateChildsModelMatrix();
                }
            }
        }

        void RecomputeModelMatrix()
        {
            Renderer::UpdateModelMatrix(m_name, GetWorldModelMatrix());
        }
        
        template <typename T>
        void AddComponent(T component);

        template <typename T>
        void OnComponentUpdated(T component)
        {
            static_assert(sizeof(T) == 0, "Component not found");
        }

        void Serialize(BlobSerializer& serializer) override;
        void Deserialize(BlobSerializer& serializer) override;
    public:
        //@TODO: make encapsulation
        std::string m_name;
        EntityId m_id;
        TagType m_Tag = 0;
        std::function<void()> m_updateFunction;
        bool isStandAlone = false;
    private:
        Entity* m_parent;
        std::vector<Ref<Entity>> m_children;
    };
}


template<>
void PHOENIX_API Phoenix::Entity::AddComponent<Phoenix::SpriteComponent>(SpriteComponent component);

template<>
void PHOENIX_API Phoenix::Entity::AddComponent<Phoenix::BoxCollider>(BoxCollider component);

template<>
void PHOENIX_API Phoenix::Entity::AddComponent<Phoenix::TransformComponent>(TransformComponent component);
