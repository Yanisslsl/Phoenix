#include "../include/MobManager.h"

#include "Windows/Core/Application/include/Application.h"

MobManager::MobManager(int maxMob)
{
    m_Mobs = std::vector<Mob*>(maxMob);
}

MobManager::~MobManager()
{
    Phoenix::EntitySubsystem* EttSubsystem = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>();
    for (int i = 0; i < m_Mobs.size(); i++)
    {
        Mob* mob = m_Mobs[i];
        EttSubsystem->DestroyEntity(EttSubsystem->GetEntityByName(mob->GetEntityName())->m_id);
        delete mob;
    }
}

void MobManager::DeleteMobs()
{
    Phoenix::EntitySubsystem* EttSubsystem = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>();
    for (int i = 0; i < m_Mobs.size(); i++)
    {
        Mob* mob = m_Mobs[i];
        if (mob != nullptr && mob->GetIsDead())
        {
            EttSubsystem->DestroyEntity(EttSubsystem->GetEntityByName(mob->GetEntityName())->m_id);
            delete mob;
            m_Mobs[i] = nullptr;
            //ToDo: Respawn Mob here
        }
    }
}

void MobManager::OnUpdate()
{
    DeleteMobs();
}

void MobManager::SpawnMob(glm::vec2 _position, Phoenix::Ref<Phoenix::Entity> _target, std::string _name)
{
    for (int i = 0; i < m_Mobs.size(); i++)
    {
        if (!m_Mobs[i]) m_Mobs[i] = new Mob(_position,_target,_name);
    }
}
