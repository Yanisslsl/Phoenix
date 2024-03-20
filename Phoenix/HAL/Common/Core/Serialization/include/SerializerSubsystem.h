#pragma once
#include <map>
#include <string>

namespace Phoenix
{
    class BlobSerializer;
    using SerializableType = uint32_t;
    enum SerializableTypes : SerializableType
    {
        SceneSerializeType = 0,
        EntitySerializeType,
        TransformComponentSerializeType,
        BoxColliderComponentSerializeType,
        SpriteComponentSerializeType,
        AnimatorComponentSerializeType
    };
  
    class ISerializable
    {
    public:
        ISerializable() = default;
        virtual void Serialize(BlobSerializer& serializer) = 0;
        virtual void Deserialize(BlobSerializer& serializer) = 0;
    };
    class SerializerSubsystem
    {
    public:
        SerializerSubsystem();
        ~SerializerSubsystem();
        void RegisterType();
        void LoadScene(std::string name);
        void SaveScene(std::string name);
    private:
        std::map<std::string, SerializableType> m_SerializableTypes;
    };
}
