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


void Knight::Update()
{
    UpdateInput();
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight");
    auto sqaurePos = entity->GetTransformPosition();
    entity->SetTransformPosition(glm::vec3(sqaurePos.x + m_X_Direction * m_Speed, sqaurePos.y + m_Y_Direction * m_Speed, 1.));
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
}
