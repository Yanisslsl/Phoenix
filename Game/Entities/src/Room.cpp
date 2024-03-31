#include "../include/Room.h"

#include "Common/Core/ECSExtended/include/TransformSubsytem.h"
#include "Utils/UUID.h"
#include "Windows/Core/Application/include/Application.h"


Room::Room():
    Room(glm::vec2(0, 0), glm::vec2(1, 1))
{
   
}

Room::Room(glm::vec2 position, glm::vec2 size)
{
    m_name = "Room";
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->BindOnStart(PX_BIND_EVENT_FN(OnStart));
}

void Room::OnStart()
{
    Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->RegisterEntityForSerialization(m_name, this);
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_name, false);
    entity->AddComponent(Phoenix::SpriteComponent("/level/room.png"));
    entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(1280/2, 740/2, 0.), 180, glm::vec2(1, 1) });
    entity->SetScale(glm::vec2(1280, 740));
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
}

void Room::Update()
{

}

void Room::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
  
}

Room::~Room()
{
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_name)->Destroy();
}

void Room::Serialize(Phoenix::BlobSerializer& serializer)
{
    auto typeId = Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->GetSerializableType(m_name);
    serializer.WriteHeader(typeId);
    serializer.WriteString(m_name);
    serializer.Write(&m_position, sizeof(m_position));
}

void Room::Deserialize(Phoenix::BlobSerializer& serializer)
{
    serializer.ReadString(m_name);
    serializer.Read(&m_position, sizeof(m_position));
}

