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

       // choose struct here for simplicity, but can be base class with specific extended components as well
      struct PHOENIX_API TransformComponent
      {
          TransformComponent(glm::vec2 transformPosition): m_Position(transformPosition) {}
          glm::vec2 GetTransformPosition() const { return m_Position; }
      private:
          glm::vec2 m_Position;
      };

    struct PHOENIX_API SpriteComponent
    {
        // here we pass the vertices and indices to the renderer maybe create specific shapes like rectangles, circles, etc with predifined vertices and indices
        explicit SpriteComponent(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout, const char* texturePath)
        {
            Renderer::CreateTexturedShape(name, vertices, indices, vertexShader, fragmentShader, bufferlayout, texturePath);
        }
    };
     /**
      * \brief Entity class, should contain all the components
      *  @TODO : Delete this class when ECS is implemented
      */
     class PHOENIX_API Entity
     {
     public:
         Entity() = default;
         Entity(std::string name)
             : m_Name(name) {}
            
         template <typename T>
         void AddComponent(T component)
         {
             m_Components.insert(std::make_pair(typeid(T).name(), component));
             OnComponentAdded<T>(component);
         }

        template <typename T>
        T& GetComponent()
        {
            return m_Components.at(typeid(T).name()).as<T>();
        }

         template <typename T>
        bool HasComponent()
        {
            return m_Components.find(typeid(T).name()) != m_Components.end();
        }

         template <typename T>
         void OnComponentAdded(T component)
         {
             static_assert(sizeof(T) == 0, "Component not found");
         }

        template <typename>
        void OnComponentAdded(SpriteComponent component)
         {
             auto c = component;
         }

        template <typename>
        void OnComponentAdded(TransformComponent component)
         {
             Renderer::UpdateShapeTransform(m_Name, component.GetTransformPosition());
         }

     private:
       std::string m_Name;
         // cannot use template data members on non static data members
       std::map<std::string, std::any> m_Components;
     };
 
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


        // Entity CreateEntity(const std::string& name = std::string());
        // Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
        // void DestroyEntity(Entity entity);

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

        Entity* CreateEntity(const std::string name);
        void DestroyEntity(std::string name);
         // Entity FindEntityByName(std::string_view name);
        // Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
         // Entity GetEntityByUUID(UUID uuid);

         bool IsRunning() const { return m_IsRunning; }
         bool IsPaused() const { return m_IsPaused; }

         void SetPaused(bool paused) { m_IsPaused = paused; }

     OrthographicCameraController& GetCameraController() { return m_CameraController; }
    private:
       
        std::map<std::string, Entity*> m_Entities;
        // @TODO: uncomment when ECS is implemented
        // std::vector<System> m_Systems;
       // void OnComponentAdded(Entity entity, T& component);
        OrthographicCameraController m_CameraController;
        bool m_IsRunning = false;
        bool m_IsPaused = false;
    };
}
