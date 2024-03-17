#include "../include/Bullet.h"

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "Common/Core/Input/include/Input.h"
#include "Utils/UUID.h"
#include "Windows/Core/Application/include/Application.h"


Bullet::Bullet(std::string id, glm::vec2 position, glm::vec2 direction)
{
    m_Direction = direction;
    m_id = id;
    self = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_id);
    self->AddComponent(Phoenix::SpriteComponent("ressources/laser_beam.png"));
    self->AddComponent(Phoenix::TransformComponent{ {position.x, position.y, 1.}, 180, glm::vec2(1, 1) });
    self->SetScale(10);
    self->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 20, 20 });
    self->AddTag(Phoenix::Tag::Bullet);
    self->BindUpdate(PX_BIND_EVENT_FN(Update));
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
   
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
    if(entity == nullptr) return;
    auto position = entity->GetTransformPosition();
    entity->SetTransformPosition(glm::vec3(position.x + m_Direction.x * m_Speed, position.y + m_Direction.y * m_Speed, 1.));
}

void Bullet::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    //@TODO: implements tags for entities
    auto i = entity->HasTag(Phoenix::Tag::Bullet);
    auto t = entity->HasTag(Phoenix::Tag::Player);
    auto m = entity->HasTag(Phoenix::Tag::Mob);
    PX_WARN("BULLET HIT");
    if(entity->HasTag(Phoenix::Tag::Bullet) || entity->HasTag(Phoenix::Tag::Player)) return;
    if(entity->HasTag(Phoenix::Tag::Mob))
    {
        entity->Destroy();
    }
    self->Destroy();
    delete this;
}



