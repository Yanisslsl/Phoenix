
#include "Common/Core/Serialization/include/SerializerSubsystem.h"

#include <fstream>

#include "Common/Core/ECSExtended/include/Entity.h"
#include "Common/Core/Serialization/include/BlobSerializer.h"
#include "Utils/FileSystem.h"
#include "Windows/Core/Application/include/Application.h"

Phoenix::SerializerSubsystem::SerializerSubsystem()
{
}

Phoenix::SerializerSubsystem::~SerializerSubsystem()
{
}

void Phoenix::SerializerSubsystem::RegisterType(std::string id, ISerializable* serializable)
{
    const auto maxValueSerializableType = std::max_element(m_SerializableTypes.begin(), m_SerializableTypes.end(), [](const auto& p1, const auto& p2) { return p1.second < p2.second; });
    auto type = serializable->GetStaticType();
    if(m_SerializableTypes.find(type) == m_SerializableTypes.end())
    {
        m_SerializableTypes[type] = maxValueSerializableType->second + 1;
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
    SceneFactory* sceneFactory = new SceneFactory();
    ISerializable* scene = sceneFactory->Create();
    scene->Deserialize(serializer);
    while(serializer.HasData()) 
    {
        BlobHeader header = serializer.ReadHeader();
        if(header.type == EntitySerializeType)
        {
            EntityFactory* entityFactory = new EntityFactory();
            ISerializable* entityFromSave = entityFactory->Create();
            entityFromSave->Deserialize(serializer);
            auto entity = dynamic_cast<Entity*>(entityFromSave);
            Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(entity->m_name);
        } else if(header.type == AnimatorComponentSerializeType)
        {
            AnimatorComponentFactory* animatorComponentFactory = new AnimatorComponentFactory();
            ISerializable* animatorComponent = animatorComponentFactory->Create();
            animatorComponent->Deserialize(serializer);
            auto animator = dynamic_cast<AnimatorComponent*>(animatorComponent);
            auto entity = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(animator->entityId);
            for(auto name : animator->names)
            {
                entity->CreateAnimation(name, animator->texturesPaths[name], animator->durations[name], animator->totalFrames[name]);
            }
        } else if(header.type == BoxColliderComponentSerializeType)
        {
            BoxColliderComponentFactory* boxColliderComponentFactory = new BoxColliderComponentFactory();
            ISerializable* boxColliderComponent = boxColliderComponentFactory->Create();
            boxColliderComponent->Deserialize(serializer);
            auto boxCollider = dynamic_cast<BoxCollider*>(boxColliderComponent);
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
            SpriteComponentFactory* spriteComponentFactory = new SpriteComponentFactory();
            ISerializable* spriteComponent = spriteComponentFactory->Create();
            spriteComponent->Deserialize(serializer);
            auto sprite = dynamic_cast<SpriteComponent*>(spriteComponent);
            auto entity = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(sprite->entityId);
            entity->AddComponent<SpriteComponent>(*sprite);
        } else if(header.type == TransformComponentSerializeType)
        {
            TransformComponentFactory* transformComponentFactory = new TransformComponentFactory();
            ISerializable* transformComponent = transformComponentFactory->Create();
            transformComponent->Deserialize(serializer);
            auto transform = dynamic_cast<TransformComponent*>(transformComponent);
            auto entity = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntityById(transform->entityId);
            entity->AddComponent<TransformComponent>(*transform);
        } else 
        {
            for(auto serializableType: m_SerializableTypes)
            {
                if(header.type == serializableType.second)
                {
                    CustomObjectFactory* customObjectFactory = new CustomObjectFactory();
                    // ISerializable* customObject = customObjectFactory->Create(entity->m_name);
                    // customObject->Serialize(serializer);
                }
            }
        }
    }
}