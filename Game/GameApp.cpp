#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Common/Core/Scene/include/OrthographicCameraController.h"
#include "Common/Core/Scene/include/Scene.h"

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
		scale = 1;
		 auto square = app->GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("square");
		 square->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::RED));
		 square->AddComponent(Phoenix::TransformComponent{ glm::vec2(x, y), 0, glm::vec2(1, 1) });
		 square->SetScale(20);
		//
		auto square1 = app->GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("square1");
		square1->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GREEN));
		square1->AddComponent(Phoenix::TransformComponent{ glm::vec2(20, 20), 0, glm::vec2(1, 1) });
		square1->SetScale(20);

		auto square2 = app->GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("square2");
		square2->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::YELLOW));
		square2->AddComponent(Phoenix::TransformComponent{ glm::vec2(20, 20), 0, glm::vec2(1, 1) });
		square2->SetScale(20);

		square1->SetRotation(45);

		square2->SetRotation(150);

		square->AddChild(square1);
		square1->AddChild(square2);

		//
		// auto isac = app->GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("isac");
		// isac->AddComponent(Phoenix::SpriteComponent{  "Isac.png" });
		// isac->AddComponent(Phoenix::TransformComponent{ glm::vec2(0,0), 0, glm::vec2(1, 1) });
		// isac->SetScale(20);
		// isac->SetTransformPosition(glm::vec2(10, 10));
		// square1->AddChild(isac);
	}

	void OnUpdate() override
	{
		const float velocity = 1;
		if(x >= 800)
		{
			direction = -1;
		} else if ( x <= 400)
        {
            direction = 1;
        }
		// x += velocity * direction;
		

		auto isac = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntity("square1");
		// isac->SetTransformPosition(glm::vec2(x, y));
		m_Scene->OnUpdate(); 
	}
	
	
	void OnEvent(Phoenix::Event& event) override
	{
		// m_CameraController.OnEvent(event);
		// PX_TRACE("Event catched {0}", event.GetName());
	}
	
private:
	Phoenix::Scene* m_Scene;
	float x;
	float y;
	float scale;
	float direction = 1;
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
