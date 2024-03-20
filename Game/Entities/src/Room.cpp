#include "../include/Room.h"

#include "Common/Core/ECSExtended/include/TransformSubsytem.h"
#include "Utils/UUID.h"
#include "Windows/Core/Application/include/Application.h"


Room::Room(glm::vec2 position, glm::vec2 size)
{
    m_id = "ROOM";
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_id);
    entity->AddComponent(Phoenix::SpriteComponent("/level/room.png"));
    entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(position.x, position.y, 0.), 180, glm::vec2(1, 1) });
    entity->SetScale(size);
    // entity->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 20, 20 });
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
}

void Room::Update()
{
    
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

