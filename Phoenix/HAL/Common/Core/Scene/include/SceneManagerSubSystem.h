// SceneManagerSubSystem.h

#pragma once
#include <map>
#include <string>

#include "Core.h"
#include "Scene.h"
#include "Common/Core/Serialization/include/AbstractFactory.h"

namespace Phoenix
{
    class PHOENIX_API SceneManagerSubSystem
    {
    public:
        SceneManagerSubSystem()
        {
            m_activeScene = nullptr;
            m_Scenes_map = std::map<std::string, Scene*>();
        }
        Scene* CreateScene(std::string name);
        void DeleteScene(std::string& name);
        Scene* GetActiveScene()
        {
            return m_activeScene;
        }
        Scene* GetScene(std::string& name) { return m_Scenes_map.at(name); }
    private:
        std::map<std::string, Scene*> m_Scenes_map;
        Scene* m_activeScene;
    };
}
