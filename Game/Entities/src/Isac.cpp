#include "../include/Isac.h"

#include "Common/Core/ECSExtended/include/Entity.h"
#include "Common/Core/Input/include/Input.h"
#include "Windows/Core/Application/include/Application.h"


Isac::Isac()
{
    m_Bullets = std::vector<Bullet*>();
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Isac");
    entity->AddComponent(Phoenix::SpriteComponent("Isac.png"));
    entity->AddComponent(Phoenix::TransformComponent{ glm::vec2(400, 400), 180, glm::vec2(1, 1) });
    entity->SetScale(30);
    entity->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 20, 20 });
    entity->BindUpdate(PX_BIND_EVENT_FN(Update));
}

void Isac::GetFireInput()
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


void Isac::GetMovementInput()
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

void Isac::UpdateInput()
{
    GetMovementInput();
    GetFireInput();
}


void Isac::Update()
{
    UpdateInput();
    std::vector<Phoenix::Ref<Phoenix::Entity>> bullets = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntitiesByTag(Phoenix::Tag::Bullet);
    for(auto bullet: m_Bullets)
    {
        bullet->Update();
    }
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Isac");
    auto sqaurePos = entity->GetTransformPosition();
    entity->SetTransformPosition(glm::vec2(sqaurePos.x + m_X_Direction * m_Speed, sqaurePos.y + m_Y_Direction * m_Speed));
}

void Isac::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    PX_INFO("Collision detected{0}", entity->GetName());
}


void Isac::Fire()
{
    auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Isac");
    auto sqaurePos = entity->GetTransformPosition();
    Bullet* bullet = new Bullet(sqaurePos, glm::vec2(m_X_Direction, m_Y_Direction));
}
