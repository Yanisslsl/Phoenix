#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Common/Core/Scene/include/Scene.h"

class ExampleLayer : public Phoenix::Layer
{
public:
	ExampleLayer(Phoenix::Application* app = nullptr)
		: Layer("Example")
	{
		m_Scene = Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->LoadScene("Example");
		x = 1280. / 10;
		y = 720. - 100;
		scale = 1;
		 auto square = app->GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("square");
		 square->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::RED));
		 square->AddComponent(Phoenix::TransformComponent{ glm::vec2(x, y), 0, glm::vec2(1, 1) });
		 square->SetScale(20);
		square->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::DYNAMIC, [](void* collider) -> void
		{
			Phoenix::BoxCollider* c = static_cast<Phoenix::BoxCollider*>(collider);
			PX_INFO("Collision detected{0}", c->position.x);
		}, Phoenix::CollisionShape::RECTANGLE, 20, 20 });

		auto square1 = app->GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("square1");
		square1->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::BLUE));
		square1->AddComponent(Phoenix::TransformComponent{ glm::vec2(x + 300, y), 0, glm::vec2(1, 1) });
		square1->SetScale(20);
		// square1->AddComponent(Phoenix::BoxCollider{ Phoenix::CollisionType::STATIC, [](void* collider) -> void
		// {
		// 	Phoenix::BoxCollider* c = static_cast<Phoenix::BoxCollider*>(collider);
		// 	PX_INFO("Collision detected{0}", c->position.x);
		// }, Phoenix::CollisionShape::RECTANGLE, 20, 20 });
		



		
	}

	void OnUpdate() override
	{
		direction++;
		// x += velocity * direction;

		auto square = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntity("square");
		// @TODO add sceneManagement subsystem
		// Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->SetCameraPosition(glm::vec3(x - direction, y, 1));
		square->SetTransformPosition(glm::vec2(x + direction, y));
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
