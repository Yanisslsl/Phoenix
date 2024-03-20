﻿// SceneManagerSubSystem.h

#pragma once
#include <map>
#include <string>

#include "Core.h"
#include "Scene.h"
#include "Windows/Core/Application/include/Application.h"
#include "Windows/Core/Window/include/Window.h"

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
        Scene* CreateScene(std::string name)
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
        void DeleteScene(std::string& name)
        {
            if(m_activeScene->GetName() == name)
            {
                PX_CORE_ASSERT(false, "You can't unload the active scene");
            }
            m_Scenes_map.erase(name);
        }

        void LoadScene(std::string name)
        {
            // auto filePath = Phoenix::FileSystem::GetAssetsPath() + "\\save\\" + "save.txt";
            // auto serializer = Phoenix::BlobSerializer(filePath);
            // auto header = serializer.ReadHeader();
            // if(header.type != SceneSerializeType)
            // {
            //     PX_CORE_ASSERT(false, "This is not a scene file");
            // }
        }

        void SaveScene(std::string name)
        {
            auto filePath = Phoenix::FileSystem::GetAssetsPath() + "\\save\\" + "save.txt";
            auto serializer = Phoenix::BlobSerializer(filePath);
            m_activeScene->Serialize(serializer);
            serializer.Flush();
        }

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
