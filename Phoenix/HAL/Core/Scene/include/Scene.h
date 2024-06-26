// Scene.h

#pragma once
#include "CameraController.h"
#include "Core.h"
#include "Core/Serialization/include/SerializerSubsystem.h"

namespace Phoenix
{
    /**
     * \brief Scene class, should contain all the entities and systems
     *        Only suited for 2D games for now with the CameraController
     */
    class PHOENIX_API Scene: public ISerializable, public Phoenix::AutoRegister<Scene>
    {
    public:
         Scene() = default;
        /**
         * \brief 
         * \param cameraController Should be instanciate with the window size
         */
         Scene(std::string& name, CameraController* cameraController);
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

         /**
          * \brief Get if the scene is running
          * \return bool whether the scene is running
          */
         bool IsRunning() const { return m_IsRunning; }

         /**
          * \brief Get if the scene is paused
          * \return bool whether the scene is paused
          */
         bool IsPaused() const { return m_IsPaused; }

         /**
          * \brief Set the scene to paused or not
          * \param paused whether the scene should be paused
          */
         void SetPaused(bool paused) { m_IsPaused = paused; }

         virtual void Serialize(BlobSerializer& serializer) override;
         virtual void Deserialize(BlobSerializer& serializer) override;

         /**
          * \brief Get the camera controller
          * \return CameraController
          */
         CameraController* GetCameraController()
         {
             return m_CameraController;
         }
    private:
        CameraController* m_CameraController;
        bool m_IsRunning = false;
        bool m_IsPaused = false;
        std::string m_Name;
    };
}
