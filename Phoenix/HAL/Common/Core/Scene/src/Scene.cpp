#include "../include/Scene.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Windows/Core/Application/include/Application.h"

namespace Phoenix
{
    Scene::Scene(std::string& name, OrthographicCameraController* cameraController)
        : m_CameraController(cameraController), m_Name(name)
    {

    }

    void Scene::OnStart()
    {
        
    }

    void Scene::OnUpdate()
    {
        Renderer::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
        Renderer::Clear();
        Renderer::BeginScene(m_CameraController->GetCamera());
        Renderer::OnUpdate();
    }

    void Scene::OnStop()
    {
        
    }

    Scene::~Scene()
    {
        
    }
}
