// Scene.h

#pragma once
#include "OrthographicCameraController.h"
#include "../../../../../Core/Core.h"
#include "Common/Core/Serialization/include/SerializerSubsystem.h"


namespace Phoenix
{
    /**
     * \brief Scene class, should contain all the entities and systems
     *        Only suited for 2D games for now with the OrthographicCameraController
     */
    class PHOENIX_API Scene: public ISerializable, public Phoenix::AutoRegister<Scene>
    {
    public:
         Scene() = default;
        /**
         * \brief 
         * \param cameraController Should be instanciate with the window size
         */
         Scene(std::string& name, OrthographicCameraController* cameraController);
         ~Scene()
         {
         };
     
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

         std::string GetName() const { return m_Name; }

        /**
         * \brief Should be called every frame, should update all the entities, and all the systems
         */
         void OnUpdate();
         bool IsRunning() const { return m_IsRunning; }
         bool IsPaused() const { return m_IsPaused; }
         void SetPaused(bool paused) { m_IsPaused = paused; }

         virtual void Serialize(BlobSerializer& serializer) override;
         virtual void Deserialize(BlobSerializer& serializer) override;
     OrthographicCameraController* GetCameraController()
         {
          return m_CameraController;
         }
     //REGISTER_CLASS_WITH_FACTORY(Scene);
    private:
        OrthographicCameraController* m_CameraController;
        bool m_IsRunning = false;
        bool m_IsPaused = false;
        std::string m_Name;
    };
}
