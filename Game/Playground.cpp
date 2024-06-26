#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Entities\include\Knight.h"
#include "Entities/include/Mob.h"
#include "Entities/include/Room.h"
#include "Utils/UUID.h"
#include "Core/ECSExtended/include/EntitySubsystem.h"
#include "ECSExtended/include/TransformSubsytem.h"



class PlaygroundLayer : public Phoenix::Layer
{
public:
	PlaygroundLayer(Phoenix::Application* app = nullptr)
		: Layer("PlaygroundLayer")
	{
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->Create3DScene("MainLevel");
		for(auto entityName : m_entities)
		{
			Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(entityName, true);
			entity->AddComponent(Phoenix::SpriteComponent("ressources/container.jpg", Phoenix::SpriteType::Cube));
			// random position
			std::random_device rd; // obtain a random number from hardware
			std::mt19937 gen(rd()); // seed the generator
			std::uniform_int_distribution<> distr(-30, 30);
			std::uniform_int_distribution<> distr1(-30, 30);
			std::uniform_int_distribution<> distr2(-30, 30);
			entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(distr(gen), distr1(gen), distr2(gen)), 180, glm::vec3(5, 5,5) });
		}
		// entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GOLD, Phoenix::SpriteType::Cube));

		// Phoenix::Ref<Phoenix::Entity> entity1 = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube1", false);
		// entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GOLD, Phoenix::SpriteType::Cube));
		// entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0.), 180, glm::vec2(1, 1) });
		// Phoenix::Ref<Phoenix::Entity> entity2 = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube", false);
		// entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GOLD, Phoenix::SpriteType::Cube));
		// entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0.), 180, glm::vec2(1, 1) });
		// Phoenix::Ref<Phoenix::Entity> entity3 = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube", false);
		// entity->AddComponent(Phoenix::SpriteComponent(Phoenix::Color::GOLD, Phoenix::SpriteType::Cube));
		// entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0.), 180, glm::vec2(1, 1) });
	}

	~PlaygroundLayer()
	{
	}
	void OnUpdate() override
	{
		Phoenix::Timer::Update();
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
		for(auto entityName : m_entities)
		{
			Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(entityName)->SetRotation(Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(entityName)->GetRotation() + 0.1f, glm::vec3(1, 1, 0));
		}
	}

	void OnEvent(Phoenix::Event& event) override
	{
	
	}
	
private:
	std::vector<std::string> m_entities = { "Cube-1", "Cube-2", "Cube-3", "Cube-4", "Cube-5", "Cube-6", "Cube-7", "Cube-8", "Cube-9", "Cube-10" };
};

class Playground : public Phoenix::Application
{
public:
	Playground(): Application(Phoenix::ApplicationMode::Wrapped)
	{
		PushLayer(new PlaygroundLayer(this));
		Run();
	}

	~Playground()
	{
		
	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new Playground();
}



