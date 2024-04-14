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
    /**
     * \brief Macro to register a class with the factory
     *        The class is registered with the factory when the program starts
     */
    #define REGISTER_CLASS_WITH_FACTORY(TYPE) \
    inline static bool Register_##TYPE = AutoRegister<TYPE>::Register(#TYPE);

    /**
     * \brief Macro to register a class with the factory
     *        The class is registered with the factory when the program starts
     */
    // workaround for static initialization order problem
    // https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
    #define REGISTER_CORE_CLASS_WITH_FACTORY(TYPE) static bool Register_Static_##TYPE = [](){bool Register = AutoRegister<TYPE>::Register(#TYPE); return true;}();

    class Entity;
    class BlobSerializer;
    using SerializableType = uint32_t;
    class Scene;

    /**
     * \brief Enum class SerializableType
     *        Used to specify the type of the core engine components serialized class
     */
    enum SerializableTypes : SerializableType
    {
        SceneSerializeType = 0,
        EntitySerializeType,
        TransformComponentSerializeType,
        BoxColliderComponentSerializeType,
        SpriteComponentSerializeType,
        AnimatorComponentSerializeType
    };

    /**
     * \brief Interface class ISerializable
     *        Used to serialize and deserialize data
     */
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

    /**
     * \brief Class TypeRegistrator
     *        Used to register the types with the factory
     */
    class TypeRegistrator : public AbstractFactory<std::string, ISerializable>
    {
    public:
        TypeRegistrator();
    };

    /**
     * \brief Class SerializerSubsystem
     *        Used to serialize and deserialize entities
     */
    class PHOENIX_API SerializerSubsystem
    {
    public:
        /**
         * \brief Constructor
         */
        SerializerSubsystem();

        /**
         * \brief Destructor
         */
        ~SerializerSubsystem();

        /**
         * \brief Register a type to m_SerializableTypes
         *        Used to store blob header information about the type
         * \param name The name of the type
         */
        static void RegisterType(std::string name);

        /**
         * \brief Know if an entity is wrapped by a custom class or not
         *        Used to know if the entity is a standalone entity or managed by a custom class
         * \param name type name
         * \return whether the entity is wrapped or not
         */
        bool HasWrappedType(std::string name);


        /**
         * \brief Save the current scene
         *        Used to save the current scene to a file
         *        Can be used when in Standalone or Wrapped mode
         */
        void SaveCurrentScene();

        /**
         * \brief Load the current scene
         *        Used to load the current scene from a file
         *        WARNING: This cannot be used in Wrapped mode, use DeserializeWrappedObjects instead
         */
        void LoadScene();

        /** 
         * \brief Deserialize the standalone objects
         * \param serializer the BlobSerializer
         */
        void DeserializeStandAloneObjects(BlobSerializer& serializer);

        /** 
         * \brief Serialize the standalone objects
         * \param serializer the BlobSerializer
         */
        void SerializeStandAloneObjects(BlobSerializer& serializer);


        /** 
         * \brief Deserialize the wrapped objects
         *        WARNING: This cannot be used in Standalone mode, use LoadScene instead
         * \return a vector of ISerializable
         */
        std::vector<Ref<ISerializable>>* DeserializeWrappedObjects();

        /** 
         * \brief Serialize the wrapped objects
         *        WARNING: This cannot be used in Standalone mode, use SaveCurrentScene instead
         * \param serializer the BlobSerializer
         */
        void SerializeWrappedObjects(BlobSerializer& serializer);

        /** 
         * \brief Register an entity for serialization
         * \param name the name of the entity
         * \param entity the entity to register
         */
        void RegisterEntityForSerialization(std::string name, ISerializable* entity);

        /** 
         * \brief Get the registered entity to serialize
         * \param name the name of the entity
         * \return the entity to serialize
         */
        ISerializable* GetRegisteredEntityToSerialize(std::string name);

         /** 
         * \brief Get the registered type id to serialize
         * \param type the type of the entity
         * \return the type id to serialize
         */
        SerializableType GetSerializableType(std::string type)
        {
            return m_SerializableTypes[type];
        }
        static TypeRegistrator factory;
    private:
        static inline std::map<std::string, SerializableType> m_SerializableTypes = {};
        std::map<std::string, ISerializable*> m_Entities_To_Serialize = {};
    };

    /**
     * \brief Class AutoRegister
     *        Used to register the types in the factory and the SerializerSubsystem
     */
    template <typename T>
    class AutoRegister {
    public:
        static bool Register(const std::string& className) {
            // register type in the factory to be able to create it
            SerializerSubsystem::factory.RegisterType<T>(className);
            // register type in the SerializerSubsystem to be able to serialize its type in the blob header and deserialize it by reading the header
            SerializerSubsystem::RegisterType(className);
            return true;
        }
    public:
        virtual ~AutoRegister() = default;
    };
}
