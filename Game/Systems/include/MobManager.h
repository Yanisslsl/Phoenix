#pragma once
#include <vector>

#include "../../Entities/include/Mob.h"
#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"


class MobManager
{
public:
    /**
     * Create a new MobManager with the max number of mobs it can handle
     */
    MobManager(int maxMob);
    ~MobManager();
    /**
     * Spawn a new mob with postion, target and name
     */
    void SpawnMob(glm::vec2 _position, Phoenix::Ref<Phoenix::Entity> _target, std::string _name);
    /**
     * Delete all the mobs considered as dead
     */
    void DeleteMobs();
    void OnUpdate();
private:
    std::vector<Mob*> m_Mobs;
};
