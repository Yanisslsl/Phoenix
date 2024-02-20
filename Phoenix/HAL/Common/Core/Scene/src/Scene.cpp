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
        Renderer::SetClearColor({ 1.0f, 5.0f, 0.0f, 1 });
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

    void Scene::DestroyEntity(std::string name)
    {
        // Application::Get().GetEntityManager()->RemoveEntity(name);
    }

}
