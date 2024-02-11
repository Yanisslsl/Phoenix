#include "../include/Scene.h"

#include "Common/Core/Graphics/Render/include/Renderer.h"

namespace Phoenix
{
    Scene::Scene(OrthographicCameraController cameraController)
        : m_CameraController(cameraController), m_Entities(std::map<std::string, Entity*>())
    {
    }

    void Scene::OnStart()
    {
        
    }

    void Scene::OnUpdate()
    {
        Phoenix::Renderer::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
        Phoenix::Renderer::Clear();
        Phoenix::Renderer::BeginScene(m_CameraController.GetCamera());
        Phoenix::Renderer::OnUpdate();
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
        m_Entities.insert(std::make_pair(name, entity));
        return entity;
    }

    void Scene::DestroyEntity(std::string name)
    {
        m_Entities.erase(name);
    }
}
