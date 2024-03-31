#include "../include/Mob.h"

#include <iostream>

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "Utils/Timer.h"
#include "Utils/UUID.h"
#include "Windows/Core/Application/include/Application.h"


Mob::Mob(glm::vec2 position, Phoenix::Ref<Phoenix::Entity> _target, std::string _name)
{
    m_id = "MOB_" + Phoenix::UUID::GenerateUUID();
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_id);
    entity->AddComponent(Phoenix::SpriteComponent("characters/mobs/mob_idle.png"));
    entity->AddComponent(Phoenix::TransformComponent{ { position.x , position.y, 1.} , 180, glm::vec2(1, 1) });
    entity->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::STATIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 50, 50 });
    entity->SetScale(30);
    entity->BindUpdate(PX_BIND_EVENT_FN(OnUpdate));
    entity->AddTag(Phoenix::Tag::Mob);
    m_target = _target;
    m_name = _name;
    speed = 50;
    isDead = false;
}

Mob::~Mob()
{
}

void Mob::OnUpdate()
{
    //We get the target position, where we want to go
    glm::vec3 targetPos = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityById(m_target->m_id)->GetTransformPosition();
    //Get self backend entity
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
    //Get self position
    glm::vec3 myPos = entity->GetTransformPosition();
    //Calculate distane between target and self
    auto distance = glm::distance(myPos,targetPos);
    //Calculate the direction
    glm::vec3 direction = glm::normalize(targetPos - myPos);
    //Calculate new position with direction, speed and delta time
    glm::vec3 newPos = myPos + (direction * speed * Phoenix::Timer::GetDeltaTime());
    //Set new position
    entity->SetTransformPosition(newPos);
}

void Mob::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    //check if mob collide with player or bullet
    if (entity->HasTag(Phoenix::Tag::Player) || entity->HasTag(Phoenix::Tag::Bullet))
    {
        PX_INFO("MOB HIT");
        //Set Entity to dead
        isDead = true;
    }
}

bool Mob::GetIsDead()
{
    return isDead;
}

std::string Mob::GetEntityName()
{
    return m_id;
}
