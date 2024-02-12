#include "../include/Scene.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"

namespace Phoenix
{
    Scene::Scene(OrthographicCameraController cameraController)
        : m_CameraController(cameraController), m_EntityManager(EntityManager())
    {
    }

    void Scene::OnStart()
    {
        
    }

    void Scene::OnUpdate()
    {
        Renderer::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
        Renderer::Clear();
        Renderer::BeginScene(m_CameraController.GetCamera());
        Renderer::OnUpdate();
    }

    void Scene::OnStop()
    {
        
    }

    Scene::~Scene()
    {
        
    }

    Entity* Scene::CreateEntity(std::string name)
    {
        Entity* entity = new Entity(name);
        m_EntityManager.AddEntity(name, entity);
        return entity;
    }

    void Scene::DestroyEntity(std::string name)
    {
        m_EntityManager.RemoveEntity(name);
    }

    Entity* Scene::GetEntity(std::string name)
    {
        return m_EntityManager.GetEntity(name);
    }
}
