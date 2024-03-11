#include "../include/Bullet.h"

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "Common/Core/Input/include/Input.h"
#include "Utils/UUID.h"
#include "Windows/Core/Application/include/Application.h"


Bullet::Bullet(glm::vec2 position, glm::vec2 direction)
{
    m_Direction = direction;
    m_id = Phoenix::UUID::GenerateUUID();
    self = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_id);
    self->AddComponent(Phoenix::SpriteComponent("bullet.png"));
    self->AddComponent(Phoenix::TransformComponent{ position, 180, glm::vec2(1, 1) });
    self->SetScale(10);
    self->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 20, 20 });
    self->AddTag(Phoenix::Tag::Bullet);
    self->BindUpdate(PX_BIND_EVENT_FN(Update));
}

Bullet::~Bullet()
{
    self->Destroy();
}

void Bullet::Update()
{
   
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
    if(entity == nullptr) return;
    auto position = entity->GetTransformPosition();
    entity->SetTransformPosition(glm::vec2(position.x + m_Direction.x * m_Speed, position.y + m_Direction.y * m_Speed));
}

void Bullet::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    //@TODO: implements tags for entities
    if(entity->m_name == "Isac") return;
    PX_WARN("BULLET HIT");
    delete this;
}



