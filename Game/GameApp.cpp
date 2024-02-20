#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Common/Core/Scene/include/OrthographicCameraController.h"
#include "Common/Core/Scene/include/Scene.h"
#include "Core/ECS/include/EntityManager.h"
#include "Core/ECS/include/TransformSystem.h"

class ExampleLayer : public Phoenix::Layer
{
public:
	ExampleLayer(Phoenix::Application* app = nullptr)
		: Layer("Example")
	{
		Phoenix::OrthographicCameraController cameraController = Phoenix::OrthographicCameraController(0.0f, 1280.0f, 0.0f, 720.0f, 1.0f, false);
		m_Scene = new Phoenix::Scene(cameraController);
		x = 1280. / 2;
		y = 720. / 2;
		isac = app->GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("hello");
		isac->AddComponent(Phoenix::SpriteComponent{ "assets/Isac.png" });
		isac->AddComponent(Phoenix::TransformComponent{ glm::vec2(x, y), glm::vec2(1, 1), glm::vec2(1, 1) });
	}

	void OnUpdate() override
	{
		x += 0.9;
		y += 0.9;
		isac->SetTransformPosition(glm::vec2(x, y));
		m_Scene->OnUpdate();
	}
	
	//
	// void OnEvent(Phoenix::Event& event) override
	// {
	// 	m_CameraController.OnEvent(event);
	// 	PX_TRACE("Event catched {0}", event.GetName());
	// }
	
private:
	Phoenix::Scene* m_Scene;
	Phoenix::Entity* isac;
	float x;
	float y;
};
class GameApp : public Phoenix::Application
{
public:
	GameApp()
	{
		// m_InputActionRegistrator->RegisterAction(Phoenix::InputAction("move", Phoenix::Key::A), PX_BIND_EVENT_FN(GameApp::TestInputActionClbk));
		PushLayer(new ExampleLayer(this));
		this->GetWindow();
	}

	~GameApp()
	{

	}

	void TestInputActionClbk()
	{
		PX_TRACE("Input action triggered");
	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new GameApp();
}
