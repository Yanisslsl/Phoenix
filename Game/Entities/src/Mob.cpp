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
    dt = 0;
}

Mob::~Mob()
{
}

void Mob::OnUpdate()
{
    dt += Phoenix::Timer::GetDeltaTime();


    //We get the target position, where we want to go
    glm::vec3 targetPos = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityById(m_target->m_id)->GetTransformPosition();
    //
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
    glm::vec3 myPos = entity->GetTransformPosition();
    auto distance = glm::distance(myPos,targetPos);
    glm::vec3 direction = glm::normalize(targetPos - myPos);
    //float dt = Phoenix::Timer::GetDeltaTime();
    PX_INFO(dt);
    //glm::vec3 speedDirection = direction * speed;
    //glm::vec3 sDAndDt = speedDirection*dt;
    //glm::vec3 tempVec3 = myPos+sDAndDt;
    glm::vec3 vec3 = myPos + (direction * speed * dt);
    entity->SetTransformPosition(vec3); //=> multiply per delta time
    dt = 0;
}

void Mob::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    //return if mob not collide with player
    if (entity->HasTag(Phoenix::Tag::Player) || entity->HasTag(Phoenix::Tag::Bullet))
    {
        PX_INFO("MOB HIT");
        //auto self = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
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
