#include "../include/MobManager.h"

#include "Windows/Core/Application/include/Application.h"

MobManager::MobManager(int maxMob)
{
    //Allocate mobs vector
    m_Mobs = std::vector<Mob*>(maxMob);
}

MobManager::~MobManager()
{
    //Get the entity subsystem
    Phoenix::EntitySubsystem* EttSubsystem = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>();
    //Loop on mobs
    for (int i = 0; i < m_Mobs.size(); i++)
    {
        Mob* mob = m_Mobs[i];
        //Destroy backend entity
        EttSubsystem->DestroyEntity(EttSubsystem->GetEntityByName(mob->GetEntityName())->m_id);
        //Delete game mob
        delete mob;
    }
}

void MobManager::DeleteMobs()
{
    //Get entity subsystem
    Phoenix::EntitySubsystem* EttSubsystem = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>();
    //Loop on mobs
    for (int i = 0; i < m_Mobs.size(); i++)
    {
        Mob* mob = m_Mobs[i];
        //check if there is a mob and it's dead 
        if (mob != nullptr && mob->GetIsDead())
        {
            //Destroy backend entity
            EttSubsystem->DestroyEntity(EttSubsystem->GetEntityByName(mob->GetEntityName())->m_id);
            //Delete game mob
            delete mob;
            //Set position in vector as nullptr
            m_Mobs[i] = nullptr;
        }
    }
}

void MobManager::OnUpdate()
{
    //On update delete mobs that need to be
    DeleteMobs();
}

void MobManager::SpawnMob(glm::vec2 _position, Phoenix::Ref<Phoenix::Entity> _target, std::string _name)
{
    //Loop on mobs
    for (int i = 0; i < m_Mobs.size(); i++)
    {
        //Check if there is no mob at this position
        if (!m_Mobs[i])
        {
            //Spawn the mob an return;
            m_Mobs[i] = new Mob(_position,_target,_name);
            return;
        }
    }
}
