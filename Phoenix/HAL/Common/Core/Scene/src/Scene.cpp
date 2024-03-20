

#include "Common/Core/Scene/include/Scene.h"

#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Common/Core/Serialization/include/BlobSerializer.h"

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

    void Scene::Serialize(BlobSerializer& serializer)
    {
        serializer.WriteHeader(SceneSerializeType);
        serializer.Write(&m_Name, sizeof(m_Name));
    }

    void Scene::Deserialize(BlobSerializer& serializer)
    {
        serializer.Read(&m_Name, sizeof(m_Name));
    }
}
