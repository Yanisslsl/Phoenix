#pragma once
#include <functional>
#include <map>
#include <string>
#include "AbstractFactory.h"
#include "Core.h"
#include "Base/Base.h"

class Room;

namespace Phoenix
{
    #define REGISTER_CLASS_WITH_FACTORY(TYPE) \
    inline static bool Register_##TYPE = AutoRegister<TYPE>::Register(#TYPE);

    // workaround for static initialization order problem
    // https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
    #define REGISTER_CORE_CLASS_WITH_FACTORY(TYPE) static bool Register_Static_##TYPE = [](){bool Register = AutoRegister<TYPE>::Register(#TYPE); return true;}();

    class Entity;
    class BlobSerializer;
    using SerializableType = uint32_t;
    class Scene;

    // @REFACTO: convert to string
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
        virtual ~ISerializable()
        {
                
        };
    };

    class TypeRegistrator : public AbstractFactory<std::string, ISerializable>
    {
    public:
        TypeRegistrator();
    };
    
    class PHOENIX_API SerializerSubsystem
    {
    public:
        SerializerSubsystem();
        ~SerializerSubsystem();
        static void RegisterType(std::string id);
        bool HasWrappedType(std::string id);
        /**
         * \brief Standalone serializer, should be used to serialize and deserialize entities
         * \param name 
         */

        void SaveCurrentScene();
        void LoadScene();
        
        void DeserializeStandAloneObjects(BlobSerializer& serializer);
        void SerializeStandAloneObjects(BlobSerializer& serializer);
        
        std::map<std::string, Ref<ISerializable>>* DeserializeWrappedObjects();
        void SerializeWrappedObjects(BlobSerializer& serializer);

        void RegisterEntityForSerialization(std::string name, ISerializable* entity);
        ISerializable* GetRegisteredEntityToSerialize(std::string name);
        
        SerializableType GetSerializableType(std::string type)
        {
            return m_SerializableTypes[type];
        }

        SerializableType GetCoreType(std::string type)
        {
            return m_SerializableTypes[type];
        }
        static TypeRegistrator factory;
    private:
        static inline std::map<std::string, SerializableType> m_SerializableTypes = {};
        std::map<std::string, ISerializable*> m_Entities_To_Serialize = {};
    };

    
    template <typename T>
    class AutoRegister {
    public:
        // Register now accepts a factory function instead of constructor arguments
        static bool Register(const std::string& className) {
            SerializerSubsystem::factory.RegisterType<T>(className);
            SerializerSubsystem::RegisterType(className);
            return true;
        }
    public:
        virtual ~AutoRegister() = default;
    };
}
