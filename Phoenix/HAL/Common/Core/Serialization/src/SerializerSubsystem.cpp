
#include "Common/Core/Serialization/include/SerializerSubsystem.h"

#include <fstream>

#include "Common/Core/ECSExtended/include/Entity.h"
#include "Common/Core/Serialization/include/BlobSerializer.h"
#include "Utils/FileSystem.h"
#include "Windows/Core/Application/include/Application.h"
#include "Common/Core/ECSExtended/include/TransformSubsytem.h"



Phoenix::MyEngineFactory Phoenix::SerializerSubsystem::factory = {};

Phoenix::SerializerSubsystem::SerializerSubsystem()
{
}

Phoenix::SerializerSubsystem::~SerializerSubsystem()
{
}

void Phoenix::SerializerSubsystem::RegisterType(std::string id)
{
    const auto maxValueSerializableType = std::max_element(m_SerializableTypes.begin(), m_SerializableTypes.end(), [](const auto& p1, const auto& p2) { return p1.second < p2.second; });
    if(m_SerializableTypes.find(id) == m_SerializableTypes.end())
    {
        m_SerializableTypes[id] = maxValueSerializableType->second + 1;
        // m_Custom_SerializableTypes[id] = serializable;
    } 
}
bool Phoenix::SerializerSubsystem::HasWrappedType(std::string id)
{
    // return m_Custom_SerializableTypes.find(id) != m_Custom_SerializableTypes.end();
    return false;
}

void Phoenix::SerializerSubsystem::SaveScene(Scene* scene)
{
    std::string filePath = FileSystem::GetAssetsPath() + "\\save\\" + "save.txt";
    BlobSerializer serializer = BlobSerializer(Mode::Write, filePath);
    scene->Serialize(serializer);
    std::vector<Ref<Entity>> entities = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntities();
    for(auto entity : entities)
    {
        if(Application::Get().GetSubSystem<SerializerSubsystem>()->HasWrappedType(entity->m_name) && entity->isStandAlone)
        {
            GetType(entity->m_name)->Serialize(serializer);
         
        } else
        {
            entity->Serialize(serializer);
        }
    }
    serializer.Flush();
}

Phoenix::ISerializable* Phoenix::SerializerSubsystem::GetType(std::string id)
{
    return nullptr;
}

void Phoenix::SerializerSubsystem::LoadScene(std::string name)
{
    std::string filePath = FileSystem::GetAssetsPath() + "\\save\\" + "save.txt";
    BlobSerializer serializer = BlobSerializer(Mode::Read, filePath);
    BlobHeader header = serializer.ReadHeader();
    if(header.type != SceneSerializeType)
    {
        PX_CORE_ASSERT(false, "Error while trying to deserialize scene. Header type is not SceneSerializeType.");
    }
    Ref<ISerializable> scene = factory.Create("Scene");
    scene->Deserialize(serializer);
    while(serializer.HasData()) 
    {
        BlobHeader header = serializer.ReadHeader();
        // @REFACTO: just get the header type and retrieve the string to pass to the factory
        if(header.type == EntitySerializeType)
        {
            Ref<ISerializable> entityFromSave = factory.Create("Entity");
            entityFromSave->Deserialize(serializer);
            auto entity = std::dynamic_pointer_cast<Entity>(entityFromSave);
            Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(entity->m_name);
        } else if(header.type == AnimatorComponentSerializeType)
        {
            Ref<ISerializable> animatorComponent = factory.Create("AnimatorComponent");
            animatorComponent->Deserialize(serializer);
            auto animator = std::dynamic_pointer_cast<AnimatorComponent>(animatorComponent);
            auto entity = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(animator->entityId);
            for(auto name : animator->names)
            {
                entity->CreateAnimation(name, animator->texturesPaths[name], animator->durations[name], animator->totalFrames[name]);
            }
        } else if(header.type == BoxColliderComponentSerializeType)
        {
            Ref<ISerializable> boxColliderComponent = factory.Create("BoxCollider");
            boxColliderComponent->Deserialize(serializer);
            auto boxCollider = std::dynamic_pointer_cast<BoxCollider>(boxColliderComponent);
            boxCollider->m_Node_Id = "";
            auto bx = new BoxCollider();
            auto d = *bx;
            boxCollider->OnHit = [](Ref<Entity> entity) { PX_CORE_INFO("OnHit function not set"); };
            auto entity = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(boxCollider->m_EntityId);
            auto u = *boxCollider;
            auto onHit = Application::Get().GetSubSystem<SerializerSubsystem>()->GetSerializableOnHitFunction(boxCollider->OnHitUuid);
            boxCollider->OnHit = onHit;
            entity->AddComponent<BoxCollider>(*boxCollider);
        } else if(header.type == SpriteComponentSerializeType)
        {
            Ref<ISerializable> spriteComponent = factory.Create("SpriteComponent");
            spriteComponent->Deserialize(serializer);
            auto sprite = std::dynamic_pointer_cast<SpriteComponent>(spriteComponent);
            auto entity = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(sprite->entityId);
            entity->AddComponent<SpriteComponent>(*sprite);
        } else if(header.type == TransformComponentSerializeType)
        {
            Ref<ISerializable> transformComponent = factory.Create("TransformComponent");
            transformComponent->Deserialize(serializer);
            auto transform = std::dynamic_pointer_cast<TransformComponent>(transformComponent);
            auto entity = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(transform->entityId);
            entity->AddComponent<TransformComponent>(*transform);
        } else 
        {
            for(auto serializableType: m_SerializableTypes)
            {
                if(header.type == serializableType.second)
                {
                    Ref<ISerializable> customSerializable = factory.Create(serializableType.first);
                    customSerializable->Deserialize(serializer);
                }
            }
        }
    }
}

Phoenix::MyEngineFactory::MyEngineFactory()
{
    REGISTER_CORE_CLASS_WITH_FACTORY(Entity)
    REGISTER_CORE_CLASS_WITH_FACTORY(TransformComponent)
}

