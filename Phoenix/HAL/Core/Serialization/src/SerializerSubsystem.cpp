#include "Core/Serialization/include/SerializerSubsystem.h"

#include <fstream>
#include <iostream>

#include "Core/Animation/include/AnimationSubsystem.h"
#include "Core/Application/include/Application.h"
#include "Core/Serialization/include/BlobSerializer.h"
#include "Utils/FileSystem.h"
#include "Core/ECSExtended/include/EntitySubsystem.h"
#include "Core/ECSExtended/include/TransformSubsytem.h"


namespace Phoenix
{
    TypeRegistrator SerializerSubsystem::factory = {};

    SerializerSubsystem::SerializerSubsystem()
    {
    }

    SerializerSubsystem::~SerializerSubsystem()
    {
    }

    void SerializerSubsystem::RegisterType(std::string id)
    {
        if(m_SerializableTypes.size() == 0)
        {
            m_SerializableTypes[id] = 0;
            return;
        } 
        const auto maxValueSerializableType = std::max_element(m_SerializableTypes.begin(), m_SerializableTypes.end(), [](const auto& p1, const auto& p2) { return p1.second < p2.second; });
        if(m_SerializableTypes.find(id) == m_SerializableTypes.end())
        {
            m_SerializableTypes[id] = maxValueSerializableType->second + 1;
        } 
    }
    bool SerializerSubsystem::HasWrappedType(std::string id)
    {
        return m_Entities_To_Serialize.find(id) != m_Entities_To_Serialize.end();
    }

    void SerializerSubsystem::DeserializeStandAloneObjects(BlobSerializer& serializer)
    {
        while(serializer.HasData()) 
        {
            BlobHeader header = serializer.ReadHeader();
            if(header.type == EntitySerializeType)
            {
                Ref<ISerializable> entityFromSave = factory.Create("Entity");
                entityFromSave->Deserialize(serializer);
                auto entity = std::dynamic_pointer_cast<Entity>(entityFromSave);
                Application::Get().GetSubSystem<EntitySubsystem>()->CreateEntity(entity->m_name);
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
                PX_CORE_ERROR("An object could not be found from deserialization process");
            }
        }
    }

    void SerializerSubsystem::SerializeStandAloneObjects(BlobSerializer& serializer)
    {
        std::vector<Ref<Entity>> entities = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntities();
        for(auto entity : entities)
        {
            if(Application::Get().GetSubSystem<SerializerSubsystem>()->HasWrappedType(entity->m_name) || !entity->isStandAlone)
            {
                PX_CORE_ERROR("You are trying to serialize wrapped objects but the application mode is set to Standalone, this may lead to undesired behaviour");
                return;
            }
            entity->Serialize(serializer);
        }
        serializer.Flush();
    }

    std::vector<Ref<ISerializable>>* SerializerSubsystem::DeserializeWrappedObjects()
    {
        std::vector<Ref<ISerializable>>* deserializedVec = new std::vector<Ref<ISerializable>>();
        std::string filePath = FileSystem::GetAssetsPath() + "\\save\\" + "save.txt";
        BlobSerializer serializer = BlobSerializer(Mode::Read, filePath);
        BlobHeader header = serializer.ReadHeader();
        if(header.type != SceneSerializeType)
        {
            PX_ERROR("Error while trying to deserialize scene. Header type is not SceneSerializeType. Aborting deserialization.");
            return deserializedVec;
        }
        Ref<ISerializable> scene = factory.Create("Scene");
        scene->Deserialize(serializer);
        while(serializer.HasData())
        {
            BlobHeader header = serializer.ReadHeader();
            for(auto serializableType: m_SerializableTypes)
            {
                if(header.type == serializableType.second)
                {
                    Ref<ISerializable> customSerializable = factory.Create(serializableType.first);
                    customSerializable->Deserialize(serializer);
                    deserializedVec->push_back(customSerializable);
                }
            }
        }
        Application::Get().GetSubSystem<EntitySubsystem>()->SetIsInitialized(true);
        return deserializedVec;
    }

    void SerializerSubsystem::SerializeWrappedObjects(BlobSerializer& serializer)
    {
        // tweak to initialise entities if save game is called before application is running
        if(!Application::Get().IsRunning() && !Application::Get().GetSubSystem<EntitySubsystem>()->IsInitialized())
        {
            Application::Get().GetSubSystem<EntitySubsystem>()->SetIsInitialized(true);
        }
        std::vector<Ref<Entity>> entities = Application::Get().GetSubSystem<EntitySubsystem>()->GetEntities();
        for(auto entity : entities)
        {
            if(!Application::Get().GetSubSystem<SerializerSubsystem>()->HasWrappedType(entity->m_name) || entity->isStandAlone)
            {
                PX_CORE_ERROR("You are trying to serialize standalone objects but the application mode is set to Wrapped, this may lead to undesired behaviour, serialization aborted for entity {0}", entity->m_name);
                return;
            }
            GetRegisteredEntityToSerialize(entity->m_name)->Serialize(serializer);
        }
        serializer.Flush();
    }

    void SerializerSubsystem::SaveCurrentScene()
    {
        Scene* scene = Application::Get().GetSubSystem<SceneManagerSubSystem>()->GetActiveScene();
        std::string filePath = FileSystem::GetAssetsPath() + "\\save\\" + "save.txt";
        BlobSerializer serializer = BlobSerializer(Mode::Write, filePath);
        scene->Serialize(serializer);
        if(Application::Get().GetMode() == ApplicationMode::Standalone)
        {
            return SerializeStandAloneObjects(serializer);
        }
        return SerializeWrappedObjects(serializer);
    }

    void SerializerSubsystem::RegisterEntityForSerialization(std::string name, ISerializable* entity)
    {
        m_Entities_To_Serialize[name] = entity;
    }

    ISerializable* SerializerSubsystem::GetRegisteredEntityToSerialize(std::string name)
    {
        return m_Entities_To_Serialize[name];
    }


    void SerializerSubsystem::LoadScene()
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
        if(Application::Get().GetMode() == ApplicationMode::Wrapped)
        {
            PX_CORE_ERROR("You are trying to load scene as standalone but the application mode is set to Wrapped, deserialzation aborted");
            return;
        }
        DeserializeStandAloneObjects(serializer);
    }


    /**
     * \brief  Registers the core classes with the factory
     *         This is needed because even if the factory is declared as static and the types are also static, the factory is not initialized
     *         Because the compiler do not know the order of the static initialization
     *         @REFACTO: This is a workaround, we need to find a better way to do this, maybe juste force the client to register his custom classes manually, and get rid of the auto registration at static initialization 
     */
    TypeRegistrator::TypeRegistrator()
    {
        REGISTER_CORE_CLASS_WITH_FACTORY(Scene)
        REGISTER_CORE_CLASS_WITH_FACTORY(Entity)
        REGISTER_CORE_CLASS_WITH_FACTORY(TransformComponent)
        REGISTER_CORE_CLASS_WITH_FACTORY(BoxCollider)
        REGISTER_CORE_CLASS_WITH_FACTORY(SpriteComponent)
        REGISTER_CORE_CLASS_WITH_FACTORY(AnimatorComponent)
    }
    
}


