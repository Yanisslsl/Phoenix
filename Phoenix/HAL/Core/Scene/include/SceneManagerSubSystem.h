#pragma once
#include <map>
#include <string>
#include "Core.h"
#include "Scene.h"

namespace Phoenix
{
    /** 
     * \brief SceneManagerSubSystem class
     *        Used to manage scenes in the application
     */
    class PHOENIX_API SceneManagerSubSystem
    {
    public:
        /** 
         * \brief Constructor
         */
        SceneManagerSubSystem()
        {
            m_activeScene = nullptr;
            m_Scenes_map = std::map<std::string, Scene*>();
        }

        /** 
         * \brief Create a new scene
         * \param name the name of the scene
         */
        Scene* CreateScene(std::string name);

        /** 
         * \brief Delete a scene
         * \param name the name of the scene
         */
        void DeleteScene(std::string& name);

        /** 
         * \brief Get the active scene
         */
        Scene* GetActiveScene()
        {
            return m_activeScene;
        }

        /** 
         * \brief Get a scene by name
         * \param name the name of the scene
         */
        Scene* GetScene(std::string& name) { return m_Scenes_map.at(name); }
    private:
        std::map<std::string, Scene*> m_Scenes_map;
        Scene* m_activeScene;
    };
}
