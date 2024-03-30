#pragma once
#include <vector>

#include "../../Entities/include/Mob.h"
#include "Base/Base.h"
#include "Common/Core/ECSExtended/include/Entity.h"


class MobManager
{
public:
    MobManager(int maxMob);
    ~MobManager();
    void SpawnMob(glm::vec2 _position, Phoenix::Ref<Phoenix::Entity> _target, std::string _name);
    void DeleteMobs();
    void OnUpdate();
private:
    std::vector<Mob*> m_Mobs;
};
