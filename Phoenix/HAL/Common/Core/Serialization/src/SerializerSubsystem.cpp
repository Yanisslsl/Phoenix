
#include "Common/Core/Serialization/include/SerializerSubsystem.h"

#include <fstream>

#include "Utils/FileSystem.h"

Phoenix::SerializerSubsystem::SerializerSubsystem()
{
}

Phoenix::SerializerSubsystem::~SerializerSubsystem()
{
}

void Phoenix::SerializerSubsystem::RegisterType()
{
    // m_SerializableTypes["TransformComponent"] = []() { return new TransformComponent(); };
    // m_SerializableTypes["BoxCollider"] = []() { return new BoxCollider(); };
    // m_SerializableTypes["SpriteComponent"] = []() { return new SpriteComponent(); };
    // m_SerializableTypes["AnimatorComponent"] = []() { return new AnimatorComponent(); };
    // m_SerializableTypes["Entity"] = []() { return new Entity(); };
}

void Phoenix::SerializerSubsystem::SaveScene(std::string name)
{
    auto filePath = FileSystem::GetAssetsPath() + "\\save\\" + "save.txt";
    std::ofstream file(filePath);
    // BlobSerializer serializer;
    // 
    // for (auto& type : m_SerializableTypes)
    // {
    //     ISerializable* serializable = type.second();
    //     serializable->Serialize(serializer);
    // }
    // 
    // serializer.SaveToFile("Scene1.scene");
}

void Phoenix::SerializerSubsystem::LoadScene(std::string name)
{
    // BlobSerializer serializer;
    // serializer.LoadFromFile("Scene1.scene");
    //
    // for (auto& type : m_SerializableTypes)
    // {
    //     ISerializable* serializable = type.second();
    //     serializable->Deserialize(serializer);
    // }
}