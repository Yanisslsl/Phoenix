#include "../include/Mob.h"
#include <iostream>
#include "Base/Base.h"
#include "Core/Application/include/Application.h"
#include "Core/ECSExtended/include/Entity.h"
#include "Utils/Timer.h"
#include "Utils/UUID.h"
#include "Core/ECSExtended/include/EntitySubsystem.h"
#include "Core/ECSExtended/include/TransformSubsytem.h"



Mob::Mob()
{
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->BindOnStart(PX_BIND_EVENT_FN(OnStart));
    m_Position = glm::vec3(450, 450, 1);
    isDead = false;
}

Mob::Mob(std::string& id, glm::vec2 position)
{
    isDead = false;
    m_id = id;
    m_Position = glm::vec3(position.x, position.y, 1);
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->BindOnStart(PX_BIND_EVENT_FN(OnStart));
}

Mob::~Mob()
{
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
    if(entity == nullptr) return;
    entity->Destroy();
}

void Mob::OnStart()
{
    Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->RegisterEntityForSerialization(m_id, this);
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_id, false);
    entity->AddComponent(Phoenix::SpriteComponent("characters/mobs/mob_idle.png"));
    entity->AddComponent(Phoenix::TransformComponent( { m_Position.x , m_Position.y, 1.} , 180, glm::vec2(1, 1) ));
    entity->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 50, 50 });
    entity->SetScale(30);
    entity->BindUpdate(PX_BIND_EVENT_FN(OnUpdate));
    entity->AddTag(Phoenix::Tag::Mob);
    speed = 30;
    dt = 0;
}

void Mob::OnUpdate()
{
    dt = Phoenix::Timer::GetDeltaTime();
    //We get the target position, where we want to go
    glm::vec3 playerPosition = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight")->GetTransformPosition();
    auto self = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
    glm::vec3 selfPosition = self->GetTransformPosition();
    float distance = glm::distance(selfPosition,playerPosition);
    glm::vec3 direction = glm::normalize(playerPosition - selfPosition);
    m_Position = selfPosition + (direction * speed * dt);
    self->SetTransformPosition(m_Position); //=> multiply per delta time
}

void Mob::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    if (entity->HasTag(Phoenix::Tag::Bullet))
    {
        auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
        entity->Destroy();
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

void Mob::Serialize(Phoenix::BlobSerializer& serializer)
{
    auto typeId = Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->GetSerializableType("Mob");
    serializer.WriteHeader(typeId);
    serializer.WriteString(m_id);
    serializer.Write(&health, sizeof(health));
    serializer.Write(&damage, sizeof(damage));
    serializer.Write(&isDead, sizeof(isDead));
    serializer.Write(&m_Position, sizeof(m_Position));
}

void Mob::Deserialize(Phoenix::BlobSerializer& serializer)
{
    serializer.ReadString(m_id);
    serializer.Read(&health, sizeof(health));
    serializer.Read(&damage, sizeof(damage));
    serializer.Read(&isDead, sizeof(isDead));
    serializer.Read(&m_Position, sizeof(m_Position));
}
