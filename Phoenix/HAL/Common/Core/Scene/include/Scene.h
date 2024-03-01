// Scene.h

#pragma once

#include <map>
#include <vector>
#include <any>
#include "OrthographicCameraController.h"
#include "../../../../../Core/Core.h"
#include "Common/Core/Graphics/DataObjects/include/Buffer.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"


namespace Phoenix
{
    /**
     * \brief Scene class, should contain all the entities and systems
     *        Only suited for 2D games for now with the OrthographicCameraController
     */
    class PHOENIX_API Scene
    {
    public:
        /**
         * \brief 
         * \param cameraController Should be instanciate with the window size
         */
         Scene(OrthographicCameraController cameraController);
         ~Scene();
     
        /**
         * \brief Start the scene, should initialize all the entities (from serialization for example)
         *        and start the game loop (if any)
         */
         void OnStart();

        /**
         * \brief Stop the scene, should stop the game loop (if any) and destroy all the entities
         *        and serialize the scene (if needed)
         */
         void OnStop();

        /**
         * \brief Should be called every frame, should update all the entities, and all the systems
         */
         void OnUpdate();
         bool IsRunning() const { return m_IsRunning; }
         bool IsPaused() const { return m_IsPaused; }
         void SetPaused(bool paused) { m_IsPaused = paused; }
     OrthographicCameraController& GetCameraController() { return m_CameraController; }
    private:
        OrthographicCameraController m_CameraController;
        bool m_IsRunning = false;
        bool m_IsPaused = false;
    };
}
