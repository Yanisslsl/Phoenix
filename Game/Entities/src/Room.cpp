#include "../include/Room.h"

#include "Common/Core/ECSExtended/include/TransformSubsytem.h"
#include "Utils/UUID.h"
#include "Windows/Core/Application/include/Application.h"


Room::Room(glm::vec2 position, glm::vec2 size)
{
    m_name = "Room";
    m_position = position;
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_name, true);
    entity->AddComponent(Phoenix::SpriteComponent("/level/room.png"));
    entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(position.x, position.y, 0.), 180, glm::vec2(1, 1) });
    entity->SetScale(size);
    // entity->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 20, 20 });
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
    Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->RegisterType(m_name, this);
}

void Room::Update()
{
    x++;
    y++;
    auto pos = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_name)->GetTransformPosition();
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_name)->SetTransformPosition(glm::vec3(pos.x + 1, pos.y + 1, 1.0));
}

void Room::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    // PX_INFO("ROOM HIT");
    // auto self = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Room");
    // self->Destroy();
}

Room::~Room()
{
    
}

void Room::Serialize(Phoenix::BlobSerializer& serializer)
{
    auto typeId = Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->GetSerializableType(m_name);
    serializer.WriteHeader(typeId);
    serializer.Write(&m_name, sizeof(m_name));
    serializer.Write(&m_position, sizeof(m_position));
}

void Room::Deserialize(Phoenix::BlobSerializer& serializer)
{
    serializer.Read(&m_name, sizeof(m_name));
}

