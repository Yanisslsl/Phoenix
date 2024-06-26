

#include "Core/Scene/include/Scene.h"

#include "Core/Graphics/Render/include/Renderer.h"
#include "Core/Serialization/include/BlobSerializer.h"
#include "Core/Serialization/include/SerializerSubsystem.h"

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

    void Scene::Serialize(BlobSerializer& serializer)
    {
        serializer.WriteHeader(SceneSerializeType);
        serializer.WriteString(m_Name);
    }

    void Scene::Deserialize(BlobSerializer& serializer)
    {
        serializer.ReadString(m_Name);
    }
}
