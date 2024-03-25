#pragma once
#include <functional>
#include <map>
#include <string>
#include "Core.h"
#include "Base/Base.h"

namespace Phoenix
{
    #define REGISTER_CLASS_WITH_FACTORY(NAME, FACTORY) \
    static bool Register_##NAME = AutoRegister<decltype(FACTORY)>::Register(NAME, FACTORY);

    class Entity;
    class BlobSerializer;
    using SerializableType = uint32_t;
    class Scene;

    // Engine Core types
    enum SerializableTypes : SerializableType
    {
        SceneSerializeType = 0,
        EntitySerializeType,
        TransformComponentSerializeType,
        BoxColliderComponentSerializeType,
        SpriteComponentSerializeType,
        AnimatorComponentSerializeType
    };


    class PHOENIX_API ISerializable
    {
    public:
        ISerializable() = default;
        virtual void Serialize(BlobSerializer& serializer) = 0;
        virtual void Deserialize(BlobSerializer& serializer) = 0;
        virtual std::string GetStaticType() = 0;
    };

  
    
    class PHOENIX_API SerializerSubsystem
    {
    public:
        SerializerSubsystem();
        ~SerializerSubsystem();
        void RegisterType(std::string id, ISerializable* serializable);
        ISerializable* GetType(std::string id);
        bool HasWrappedType(std::string id);
        void LoadScene(std::string name);
        void SaveScene(Scene* scene);
        void RegisterSerializableUpdateFunction(unsigned int uuid, std::function<void()> func)
        {
            m_SerializableMapUpdateFunctions[uuid] = func;
        }
        void RegisterSerializableOnHitFunction(unsigned int uuid, std::function<void(Ref<Entity>)> func)
        {
            m_SerializableMapOnHitFunctions[uuid] = func;
        }

        SerializableType GetSerializableType(std::string type)
        {
            return m_SerializableTypes[type];
        }

        std::function<void(Ref<Entity>)> GetSerializableOnHitFunction(unsigned int uuid)
        {
            return m_SerializableMapOnHitFunctions[uuid];
        }
        
        SerializableType GetCoreType(std::string type)
        {
            return m_SerializableTypes[type];
        }

        std::function<void()> GetSerializableUpdateFunction(unsigned int uuid)
        {
            return m_SerializableMapUpdateFunctions[uuid];
        }
        using FactoryFunc = std::function<std::unique_ptr<ISerializable>()>;
        static std::unordered_map<std::string, FactoryFunc> classRegistry;

    private:
        std::map<std::string, SerializableType> m_SerializableTypes = {
            {"Scene", SceneSerializeType},
            {"Entity", EntitySerializeType},
            {"TransformComponent", TransformComponentSerializeType},
            {"BoxColliderComponent", BoxColliderComponentSerializeType},
            {"SpriteComponent", SpriteComponentSerializeType},
            {"AnimatorComponent", AnimatorComponentSerializeType}
        };
        // std::map<std::string, std::function<ISerializable*>> m_Custom_SerializableTypes;
        std::map<unsigned int, std::function<void()>> m_SerializableMapUpdateFunctions;
        std::map<unsigned int, std::function<void(Ref<Entity>)>> m_SerializableMapOnHitFunctions;
    };

    template <typename T, typename... Args>
    class AutoRegister {
        friend SerializerSubsystem;
    protected:
        // Register now accepts a factory function instead of constructor arguments
        static bool Register(const std::string& className, std::function<std::unique_ptr<ISerializable>(Args ...args)> factory) {
            SerializerSubsystem::classRegistry[className] = factory;
            return true;
        }
    public:
        virtual ~AutoRegister() = default;
    };
}
