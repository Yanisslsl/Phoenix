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
    // class EntityOld;
    //
    // class EntityManagerOld
    // {
    // public: 
    //     EntityManagerOld(): m_Entities(std::map<std::string, EntityOld*>{}) {}
    //
    //     EntityOld* AddEntity(std::string name, EntityOld* entity)
    //     {
    //         m_Entities.insert(std::make_pair(name, entity));
    //         return entity;
    //     }
    //
    //     EntityOld* RemoveEntity(std::string name)
    //     {
    //         auto entity = m_Entities.at(name);
    //         m_Entities.erase(name);
    //         return entity;
    //     }
    //
    //     EntityOld* GetEntity(std::string name)
    //     {
    //         return m_Entities.at(name);
    //     }
    // private:
    //     std::map<std::string, EntityOld*> m_Entities;
    // };
    //
    //  struct Component
    //  {
    //      Component(std::string entityId): m_Entity_Name(entityId) {} 
    //     virtual ~Component() = default;
    //      virtual void OnStart() = 0;
    //      virtual void OnStop() = 0;
    //      virtual void OnUpdate() = 0;
    //      
    //  private:
    //      //@TODO: change to UUID, maybe pass to 
    //      std::string m_Entity_Name;
    //  };
    //
    //
    //    // choose struct here for simplicity, but can be base class with specific extended components as well
    //   struct PHOENIX_API TransformComponent: public Component
    //   {
    //       TransformComponent(std::string name, glm::vec2 transformPosition): m_Position(transformPosition), Component(name) {};
    //       glm::vec2 GetTransformPosition() const { return m_Position; }
    //
    //       virtual void OnStart() override
    //       {
    //       }
    //       virtual void OnStop() override
    //       {
    //       }
    //       virtual void OnUpdate() override
    //       {
    //       }
    //   private:
    //       glm::vec2 m_Position;
    //   };
    //
    // struct PHOENIX_API SpriteComponent: public Component
    // {
    //     
    //     // @TODO here we pass the vertices and indices to the renderer maybe create specific shapes like rectangles, circles, etc with predifined vertices and indices
    //     explicit SpriteComponent(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout, const char* texturePath): Component(name)
    //     {
    //         // Here we do not bother about the specific shape, we just create a raw quad as we are in 2D
    //         Renderer::CreateTexturedShape(name, vertices, indices, vertexShader, fragmentShader, bufferlayout, texturePath);
    //     }
    //
    //     explicit SpriteComponent(std::string name, const char* texturePath, glm::vec2 transform = {}): Component(name)
    //     {
    //         Renderer::CreateQuad(name, texturePath, glm::vec2(0.0f));
    //     }
    //
    //     virtual void OnStart() override
    //     {
    //     }
    //     virtual void OnStop() override
    //     {
    //     }
    //     virtual void OnUpdate() override
    //     {
    //     }
    // };
    //  /**
    //   * \brief Entity class, should contain all the components
    //   *  @TODO : Delete this class when ECS is implemented
    //   */
    //  class PHOENIX_API EntityOld
    //  {
    //  public:
    //      EntityOld() = default;
    //      EntityOld(std::string name)
    //          : m_Name(name) {}
    //         
    //      template <typename T>
    //      void AddComponent(T component)
    //      {
    //          m_Components.insert(std::make_pair(typeid(T).name(), component));
    //          OnComponentAdded<T>(component);
    //      }
    //
    //     template <typename T>
    //     T& GetComponent()
    //     {
    //         return m_Components.at(typeid(T).name()).as<T>();
    //     }
    //
    //     template <typename T>
    //     bool HasComponent()
    //     {
    //         return m_Components.find(typeid(T).name()) != m_Components.end();
    //     }
    //
    //      template <typename T>
    //      void OnComponentAdded(T component)
    //      {
    //      }
    //
    //      template <typename >
    //      void OnComponentAdded(Component& component)
    //      {
    //          
    //      }
    //
    //     template <typename>
    //     void OnComponentAdded(SpriteComponent& component)
    //      {
    //      }
    //
    //     template <typename>
    //     void OnComponentAdded(TransformComponent& component)
    //      {
    //          Renderer::UpdateShapeTransform(m_Name, component.GetTransformPosition());
    //      }
    //
    //  private:
    //    std::string m_Name;
    //      // cannot use template data members on non static data members
    //    std::map<std::string, std::any> m_Components;
    //  };
    //
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

        void DestroyEntity(std::string name);
         // Entity FindEntityByName(std::string_view name);
        // Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
         // Entity GetEntityByUUID(UUID uuid);

         bool IsRunning() const { return m_IsRunning; }
         bool IsPaused() const { return m_IsPaused; }

         void SetPaused(bool paused) { m_IsPaused = paused; }


     OrthographicCameraController& GetCameraController() { return m_CameraController; }
    private:
       
        // @TODO: uncomment when ECS is implemented
        // std::vector<System> m_Systems;
       // void OnComponentAdded(Entity entity, T& component);
        OrthographicCameraController m_CameraController;
        bool m_IsRunning = false;
        bool m_IsPaused = false;
    };
}
