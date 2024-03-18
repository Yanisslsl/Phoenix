#include "..\include\Knight.h"

#include "Common/Core/ECSExtended/include/Entity.h"
#include "Common/Core/Input/include/Input.h"
#include "Windows/Core/Application/include/Application.h"


Knight::Knight()
{
    m_Bullets = std::vector<Bullet*>();
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Knight");
    entity->AddComponent(Phoenix::SpriteComponent("characters/player/player_idle.png"));
    entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(400, 400, 1.), 180, glm::vec2(1, 1) });
    entity->SetScale(30);
    entity->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 20, 20 });
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
    entity->AddTag(Phoenix::Tag::Player);
    std::vector<std::string> runAnimationsRightTextures = { "characters/player/animation_run/right/player_run_1.png", "characters/player/animation_run/right/player_run_2.png", "characters/player/animation_run/right/player_run_3.png", "characters/player/animation_run/right/player_run_4.png" };
    std::vector<std::string> runAnimationsLeftTextures = { "characters/player/animation_run/left/player_run_1.png", "characters/player/animation_run/left/player_run_2.png", "characters/player/animation_run/left/player_run_3.png", "characters/player/animation_run/left/player_run_4.png" };
    entity->CreateAnimation("RunRight", runAnimationsRightTextures, .3, 4);
    entity->CreateAnimation("RunLeft", runAnimationsLeftTextures, .3, 4);
    
    std::vector<std::string> fireAnimationsRightTextures = { "characters/player/animation_fire/right/player_fire_1.png", "characters/player/animation_fire/right/player_fire_2.png", "characters/player/animation_fire/right/player_fire_3.png", "characters/player/animation_fire/right/player_fire_4.png" };
    std::vector<std::string> fireAnimationsLeftTextures = { "characters/player/animation_fire/left/player_fire_1.png", "characters/player/animation_fire/left/player_fire_2.png", "characters/player/animation_fire/left/player_fire_3.png", "characters/player/animation_fire/left/player_fire_4.png" };
    entity->CreateAnimation("FireRight", fireAnimationsRightTextures, .05, 4);
    entity->CreateAnimation("FireLeft", fireAnimationsLeftTextures, .05, 4);
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
    } 
    if(Phoenix::Input::IsKeyPressed(Phoenix::Key::Left))
    {
        m_X_Direction = -1;
    } 
    if(Phoenix::Input::IsKeyPressed(Phoenix::Key::Down))
    {
        m_Y_Direction = 1;
    } 
    if(Phoenix::Input::IsKeyPressed(Phoenix::Key::Up))
    {
        m_Y_Direction = -1;
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
    // else if (m_State == State::FIRE_RIGHT)
    // {
    //     PX_WARN("FIRE RIGHT");
    //     entity->Play("FireRight", [&](){
    //         // m_State = State::RUN_RIGHT;
    //         // m_isStateDirty = true;
    //     });
    // }
    // else if (m_State == State::FIRE_LEFT)
    // {
    //     PX_WARN("FIRE LEFT");
    //     entity->Play("FireLeft", [&](){
    //         // m_State = State::RUN_LEFT;
    //         // m_isStateDirty = true;
    //     });
    // }
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
    auto sqaurePos = entity->GetTransformPosition();
    entity->SetTransformPosition(glm::vec3(sqaurePos.x + m_X_Direction * m_Speed, sqaurePos.y + m_Y_Direction * m_Speed, 1.));
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
}

void Knight::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    PX_INFO("Collision detected{0}", entity->GetName());
}


void Knight::Fire()
{
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight");
    auto sqaurePos = entity->GetTransformPosition();
    auto bulletId = "Bullet - " + std::to_string(++m_BulletCount);
    Bullet* bullet = new Bullet(bulletId, sqaurePos, glm::vec2(m_X_Direction, m_Y_Direction));
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
