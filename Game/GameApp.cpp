#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Entities\include\Knight.h"
#include "Entities/include/Mob.h"
#include "Entities/include/Room.h"
#include "Utils/UUID.h"
#include "Core/ECSExtended/include/EntitySubsystem.h"
class MainLayer : public Phoenix::Layer
{
public:
	MainLayer(Phoenix::Application* app = nullptr)
		: Layer("MainLayer")
	{
		m_Entities = new std::vector<Phoenix::Ref<Phoenix::ISerializable>>();
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->CreateScene("MainLevel");
		InitLevel();
		SpawnMob();
		SpawnMob();
		SpawnMob();
		Phoenix::Application::Get().GetSubSystem<Phoenix::InputActionRegistratorSubSystem>()->RegisterAction(Phoenix::InputAction("SaveGame", Phoenix::Key::S), PX_BIND_EVENT_FN(SaveGame));
		Phoenix::Application::Get().GetSubSystem<Phoenix::InputActionRegistratorSubSystem>()->RegisterAction(Phoenix::InputAction("Delete", Phoenix::Key::D), PX_BIND_EVENT_FN(Delete));
		Phoenix::Application::Get().GetSubSystem<Phoenix::InputActionRegistratorSubSystem>()->RegisterAction(Phoenix::InputAction("LoadGame", Phoenix::Key::L), PX_BIND_EVENT_FN(LoadGame));
	}

	~MainLayer()
	{
		delete m_Entities;
	}

	void SpawnMob()
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(50, 1200);
		std::uniform_int_distribution<> distr1(20, 600);
		std::string mobId = "MOB_" + Phoenix::UUID::GenerateUUID();
		m_Entities->push_back(std::make_shared<Mob>(mobId, glm::vec2(distr(gen), distr1(gen))));
		Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->SetIsInitialized(true);
	}

	void SpawnMobOnInterval()
	{
		float dt = Phoenix::Timer::GetDeltaTime() * 100;
		m_Delta += dt;
		if(m_Delta > 30)
		{
			SpawnMob();
			m_Delta = 0;
		}
	}

	void Delete()
	{
		m_Entities->clear();
	}

	void SaveGame()
	{
		Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->SaveCurrentScene();
	}

	void LoadGame()
	{
		Delete();
		m_Entities = Phoenix::Application::Get().GetSubSystem<Phoenix::SerializerSubsystem>()->DeserializeWrappedObjects();
	}

	void InitLevel()
	{
		m_Entities->push_back(std::make_shared<Room>());
		m_Entities->push_back(std::make_shared<Knight>());
	}


	void OnUpdate() override
	{
		Phoenix::Timer::Update();
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
		SpawnMobOnInterval();
	}

	void OnEvent(Phoenix::Event& event) override
	{
		// m_CameraController.OnEvent(event);
		// PX_TRACE("Event catched {0}", event.GetName());
	}
	
private:
	Knight* m_player;
	std::vector<glm::vec2> m_mob_positions;
	float xPos = 0;
	float yPos = 0;
	std::vector<std::string> m_Ids;
	std::vector<Phoenix::Ref<Phoenix::ISerializable>>* m_Entities;
	std::vector<Mob*> m_mobs;
	float m_Delta = 0;
	std::vector<std::string> entitiesToDelete;
	
};
class GameApp : public Phoenix::Application
{
public:
	GameApp(): Application(Phoenix::ApplicationMode::Wrapped)
	{
		PushLayer(new MainLayer(this));
		Run();
	}

	~GameApp()
	{
		
	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new GameApp();
}
