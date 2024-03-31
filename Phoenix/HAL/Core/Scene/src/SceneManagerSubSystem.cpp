
#include "Core/Scene/include/SceneManagerSubSystem.h"

#include "Core/Scene/include/Scene.h"

namespace Phoenix
{
    Scene* SceneManagerSubSystem::CreateScene(std::string name)
    {
        // Set as static for now
        auto cameraController = new OrthographicCameraController(0.0f, 1280, 720 , 1.0f, false);
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
            PX_CORE_ASSERT(false, "You can't unload the active scene");
        }
        m_Scenes_map.erase(name);
    }
}
