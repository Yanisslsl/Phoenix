

#include "Core/Scene/include/Scene.h"

#include "Core/Application/include/Application.h"
#include "Core/Graphics/Render/include/Renderer.h"
#include "Core/Serialization/include/BlobSerializer.h"
#include "Core/Serialization/include/SerializerSubsystem.h"

namespace Phoenix
{
    Scene::Scene(std::string& name, CameraController* cameraController)
        : m_CameraController(cameraController), m_Name(name)
    {

    }

    void Scene::OnStart()
    {
        
    }

    void Scene::OnUpdate()
    {
        Application::Get().GetRenderer()->SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
        Application::Get().GetRenderer()->Clear();
        Application::Get().GetRenderer()->BeginScene(m_CameraController->GetCamera());
        Application::Get().GetRenderer()->OnUpdate();
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
