#include "../include/Mob.h"

#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"
#include "Utils/UUID.h"
#include "Windows/Core/Application/include/Application.h"


Mob::Mob(glm::vec2 position)
{
    m_id = Phoenix::UUID::GenerateUUID();
    Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(m_id);
    entity->AddComponent(Phoenix::SpriteComponent("Mob.png"));
    entity->AddComponent(Phoenix::TransformComponent{ position, 180, glm::vec2(1, 1) });
    entity->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::STATIC, PX_BIND_EVENT_FN(OnHit), Phoenix::CollisionShape::RECTANGLE, 50, 50 });
    entity->SetScale(30);
    entity->BindUpdate(PX_BIND_EVENT_FN(OnUpdate));
}


void Mob::OnUpdate()
{
    
}

void Mob::OnHit(Phoenix::Ref<Phoenix::Entity> entity)
{
    PX_INFO("MOB HIT");
    auto self = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(m_id);
    self->Destroy();
}
