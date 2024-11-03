#include "Core/Application/include/Application.h"
#include "Core/ECSExtended/include/Entity.h"
#include "Core/Input/include/Input.h"
#include "Utils/UUID.h"
#include "../include/Knight.h"
#include "Core/ECSExtended/include/EntitySubsystem.h"
#include "Core/ECSExtended/include/TransformSubsytem.h"

Knight::Knight()
{
    m_name = "Knight";
    m_Position = glm::vec2(400, 400);
    Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->BindOnStart(PX_BIND_EVENT_FN(OnStart));
}

Knight::~Knight()
{
}

void Knight::OnStart()
{
    Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->RegisterEntityForSerialization(m_name, this);
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Knight", false);
    entity->AddComponent(Phoenix::SpriteComponent("characters/player/player_idle.png", Phoenix::SpriteType::Quad));
    entity->AddComponent(Phoenix::TransformComponent(glm::vec3(m_Position.x, m_Position.y, 1.), 180, glm::vec3(1, 1,1) ));
    entity->SetScale(30);
    entity->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 20, 20 });
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
    entity->AddTag(Phoenix::Tag::Player);
    std::vector<std::string> runAnimationsRightTextures = { "characters/player/animation_run/right/player_run_1.png", "characters/player/animation_run/right/player_run_2.png", "characters/player/animation_run/right/player_run_3.png", "characters/player/animation_run/right/player_run_4.png" };
    std::vector<std::string> runAnimationsLeftTextures = { "characters/player/animation_run/left/player_run_1.png", "characters/player/animation_run/left/player_run_2.png", "characters/player/animation_run/left/player_run_3.png", "characters/player/animation_run/left/player_run_4.png" };
    entity->CreateAnimation("RunRight", runAnimationsRightTextures, (float).3, (float)4);
    entity->CreateAnimation("RunLeft", runAnimationsLeftTextures, (float).3, (float)4);
    std::vector<std::string> fireAnimationsRightTextures = { "characters/player/animation_fire/right/player_fire_1.png", "characters/player/animation_fire/right/player_fire_2.png", "characters/player/animation_fire/right/player_fire_3.png", "characters/player/animation_fire/right/player_fire_4.png" };
    std::vector<std::string> fireAnimationsLeftTextures = { "characters/player/animation_fire/left/player_fire_1.png", "characters/player/animation_fire/left/player_fire_2.png", "characters/player/animation_fire/left/player_fire_3.png", "characters/player/animation_fire/left/player_fire_4.png" };
    entity->CreateAnimation("FireRight", fireAnimationsRightTextures, (float).05, 4);
    entity->CreateAnimation("FireLeft", fireAnimationsLeftTextures, (float).05, 4);
}

void Knight::GetFireInput()
{
        if(Phoenix::Input::IsKeyPressed(Phoenix::Key::Space))
        {
            m_count++;
            if(m_count % 10 == 0)
            {
                Fire();
            }
        }
}

void Knight::GetMovementInput()
{
    m_X_Direction = 0;
    m_Y_Direction = 0;
    if(Phoenix::Input::IsKeyPressed(Phoenix::Key::Right))
    {
        m_X_Direction = 1;
        m_Last_Y_Direction = 0;
        m_Last_X_Direction = 1;
    } 
    if(Phoenix::Input::IsKeyPressed(Phoenix::Key::Left))
    {
        m_Last_Y_Direction = 0;
        m_Last_X_Direction = -1;
        m_X_Direction = -1;
    } 
    if(Phoenix::Input::IsKeyPressed(Phoenix::Key::Down))
    {
        m_Y_Direction = 1;
        m_Last_Y_Direction = 1;
        m_Last_X_Direction = 0;
    } 
    if(Phoenix::Input::IsKeyPressed(Phoenix::Key::Up))
    {
        m_Y_Direction = -1;
        m_Last_Y_Direction = -1;
        m_Last_X_Direction = 0;
    }
}

void Knight::UpdateInput()
{
    GetMovementInput();
    GetFireInput();
}

void Knight::PlayAnimation()
{
    if(!m_isStateDirty) return;
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight");
    if(m_State == State::RUN_RIGHT)
    {
        entity->Play("RunRight");
    }
    else if (m_State == State::RUN_LEFT)
    {
        entity->Play("RunLeft");
    }
    m_isStateDirty = false;
}

void Knight::Update()
{
    UpdateInput();
    PlayAnimation();
    Move();
}

void Knight::Move()
{
    if(m_X_Direction == 0 && m_Y_Direction == 0) return;
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight");
    m_Position = entity->GetTransformPosition();
    if(m_Position.x <= 1280 && m_Position.x >= 0 && m_Position.y <= 720 && m_Position.y >= 0)
    {
        entity->SetTransformPosition(glm::vec3(m_Position.x + m_X_Direction * m_Speed, m_Position.y + m_Y_Direction * m_Speed, 1.));
        if(m_State == State::FIRE_RIGHT || m_State == State::FIRE_RIGHT) return;
        if(m_X_Direction == -1 && m_State != State::RUN_RIGHT)
        {
            m_State = State::RUN_RIGHT;
            m_isStateDirty = true;
        } else if(m_X_Direction == 1 && m_State != State::RUN_LEFT)
        {
            m_State = State::RUN_LEFT;
            m_isStateDirty = true;
        }
    } else
    {
        if(m_Position.x >= 1280)
        {
            entity->SetTransformPosition(glm::vec3(1279, m_Position.y, 1.));
        } else if(m_Position.x <= 0)
        {
            entity->SetTransformPosition(glm::vec3(1, m_Position.y, 1.));
        } else if(m_Position.y >= 720)
        {
            entity->SetTransformPosition(glm::vec3(m_Position.x, 719, 1.));
        } else if(m_Position.y <= 0)
        {
            entity->SetTransformPosition(glm::vec3(m_Position.x, 1, 1.));
        }
    }
}

void Knight::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    
}


void Knight::Fire()
{
    int directionX = 0;
    int directionY = 0;
    if(m_X_Direction == 0 && m_Y_Direction == 0)
    {
        directionX = m_Last_X_Direction;
        directionY = m_Last_Y_Direction;
    } else
    { 
        directionX = m_X_Direction;
        directionY = m_Y_Direction;
    }
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight");
    auto sqaurePos = entity->GetTransformPosition();
    auto bulletId = "Bullet - " + std::to_string(++m_BulletCount);
    Bullet* bullet = new Bullet(bulletId, sqaurePos, glm::vec2(directionX, directionY));
    if(m_State == State::RUN_RIGHT)
    {
        entity->Play("FireRight", [&](){
         m_State = State::RUN_RIGHT;
         m_isStateDirty = true;
     });
    }
    else if(m_State == State::RUN_LEFT)
    {
        entity->Play("FireLeft", [&](){
         m_State = State::RUN_LEFT;
         m_isStateDirty = true;
     });
    }
}

void Knight::Serialize(Phoenix::BlobSerializer& serializer)
{
    auto typeId = Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->GetSerializableType(m_name);
    serializer.WriteHeader(typeId);
    serializer.Write(&m_Position, sizeof(m_Position));
    serializer.Write(&m_X_Direction, sizeof(m_X_Direction));
    serializer.Write(&m_Y_Direction, sizeof(m_Y_Direction));
    serializer.Write(&m_Speed, sizeof(m_Speed));
    serializer.Write(&m_count, sizeof(m_count));
    serializer.Write(&m_BulletCount, sizeof(m_BulletCount));
    serializer.WriteString(m_name);
    serializer.Write(&m_State, sizeof(m_State));
    serializer.Write(&m_isStateDirty, sizeof(m_isStateDirty));
}

void Knight::Deserialize(Phoenix::BlobSerializer& serializer)
{
    serializer.Read(&m_Position, sizeof(m_Position));
    serializer.Read(&m_X_Direction, sizeof(m_X_Direction));
    serializer.Read(&m_Y_Direction, sizeof(m_Y_Direction));
    serializer.Read(&m_Speed, sizeof(m_Speed));
    serializer.Read(&m_count, sizeof(m_count));
    serializer.Read(&m_BulletCount, sizeof(m_BulletCount));
    serializer.ReadString(m_name);
    serializer.Read(&m_State, sizeof(m_State));
    serializer.Read(&m_isStateDirty, sizeof(m_isStateDirty));
}

