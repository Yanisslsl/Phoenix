#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Common/Core/Scene/include/Scene.h"
#include "Entities\include\Knight.h"
#include "Entities/include/Mob.h"
#include "Entities/include/Room.h"
#include "Systems/include/MobManager.h"
#include "Utils/UUID.h"

class MainLayer : public Phoenix::Layer
{
public:
	MainLayer(Phoenix::Application* app = nullptr)
		: Layer("MainLayer")
	{
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->LoadScene("MainLevel");
		InitLevel();

		m_mobManager = new MobManager(7);
		
		m_mobManager->SpawnMob(glm::vec2(0, 0),Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight"),"Mob1");
		m_mobManager->SpawnMob(glm::vec2(1200, 700),Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight"),"Mob2");
		m_mobManager->SpawnMob(glm::vec2(600, 500),Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight"),"Mob3");
		m_mobManager->SpawnMob(glm::vec2(400, 600),Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight"),"Mob4");
		m_mobManager->SpawnMob(glm::vec2(600, 400),Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight"),"Mob5");
		m_mobManager->SpawnMob(glm::vec2(500, 400),Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight"),"Mob6");
		m_mobManager->SpawnMob(glm::vec2(400, 500),Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Knight"),"Mob7");
		
		// std::random_device rd; // obtain a random number from hardware
		// std::mt19937 gen(rd()); // seed the generator
		// std::uniform_int_distribution<> distr(50, 1200);
		// std::uniform_int_distribution<> distr1(20, 600);
		//
		// for(int i = 0; i < 50; i++)
		// {
		// 	m_mob_positions.push_back(glm::vec2(distr(gen), distr1(gen)));
		// }
		// for(auto position: m_mob_positions)
		// {
		// 	m_mobs.push_back(new Mob(position));
		// }
	}

	void Benchmark()
	{
		// benchmarking max entities rendering performance now max is 200 without FPS drop
		// need batch rendering or instancing
		// for (int i = 0; i < 100; i++)
		// {
		// 	auto id = Phoenix::UUID::GenerateUUID();
		// 	m_Ids.push_back(id);
		// 	// xPos += 2;
		// 	// yPos += 2;
		// 	Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(id);
		// 	entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::RED));
		// 	entity->AddComponent(Phoenix::TransformComponent{ glm::vec2(xPos, yPos), 180, glm::vec2(1, 1) });
		// 	entity->SetScale(30);
		// }
	}

	void InitLevel()
	{
		auto width = Phoenix::Application::Get().GetWindow()->GetWidth();
		auto height = Phoenix::Application::Get().GetWindow()->GetHeight();
		// @TODO: FIX MEMORY LEAK
		new Room(glm::vec2(width/2, height/2), glm::vec2(width, height));
		new Knight();
	}

	void OnUpdate() override
	{
		// for(auto id: m_Ids)
		// {
		// 	auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(id);
		// 	auto position = entity->GetTransformPosition();
		// 	entity->SetTransformPosition(glm::vec2(position.x + 1, position.y + 1));
		// }
		Phoenix::Timer::Update();
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
		m_mobManager->OnUpdate();
	}
	
	void OnEvent(Phoenix::Event& event) override
	{
		// m_CameraController.OnEvent(event);
		// PX_TRACE("Event catched {0}", event.GetName());
	}
	
private:
	Knight* m_player;
	MobManager* m_mobManager;
	std::vector<glm::vec2> m_mob_positions;
	float xPos = 0;
	float yPos = 0;
	std::vector<std::string> m_Ids;
	
};
class GameApp : public Phoenix::Application
{
public:
	GameApp()
	{
		PushLayer(new MainLayer(this));
	}

	~GameApp()
	{

	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new GameApp();
}
