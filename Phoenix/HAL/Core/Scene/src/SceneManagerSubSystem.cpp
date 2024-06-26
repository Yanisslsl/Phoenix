
#include "Core/Scene/include/SceneManagerSubSystem.h"

#include "Core/Application/include/Application.h"
#include "Core/Scene/include/Scene.h"

namespace Phoenix
{
    Scene* SceneManagerSubSystem::Create2DScene(std::string name)
    {
        auto cameraController = new CameraController(0.0f, 1280, 720.0 , 1.0f, 1280.0/720.0, false);
        auto scene = new Scene(name, cameraController);
        m_Scenes_map.insert(std::pair<std::string, Scene*>(name, scene));
        if(!m_activeScene)
        {
            m_activeScene = scene;
        }
        return scene;
    }

    Scene* SceneManagerSubSystem::Create3DScene(std::string name)
    {
        auto cameraController = new CameraController(45.0f, 1280, 720.0 , 0.1f, 100.0);
        auto scene = new Scene(name, cameraController);
        m_Scenes_map.insert(std::pair<std::string, Scene*>(name, scene));
        if(!m_activeScene)
        {
            m_activeScene = scene;
        }
        return scene;
    }

    void SceneManagerSubSystem::DeleteScene(std::string& name)
    {
        if(m_activeScene->GetName() == name)
        {
            PX_ERROR("You can't unload the active scene");
        }
        m_Scenes_map.erase(name);
    }
}
