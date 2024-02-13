#include "../include/Scene.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Windows/Core/Application/include/Application.h"

namespace Phoenix
{
    Scene::Scene(OrthographicCameraController cameraController)
        : m_CameraController(cameraController)
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
        Application::Get().GetEntityManager()->AddEntity(name, entity);
        return entity;
    }

    void Scene::DestroyEntity(std::string name)
    {
        Application::Get().GetEntityManager()->RemoveEntity(name);
    }

    Entity* Scene::GetEntity(std::string name)
    {
        Application::Get().GetEntityManager()->GetEntity(name);
    }
}
