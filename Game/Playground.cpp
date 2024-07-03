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
	
		Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube", true);
		entity->AddComponent(Phoenix::SpriteComponent("ressources/container.jpg", Phoenix::SpriteType::Cube));
		entity->AddComponent(Phoenix::TransformComponent{ glm::vec3(0, 0, 0), 180, glm::vec3(5, 5,5) });
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
		Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Cube")->SetRotation(Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName("Cube")->GetRotation() + 0.1f, glm::vec3(1, 1, 0));
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
	}

	void OnEvent(Phoenix::Event& event) override
	{
	
	}
	
private:
	std::vector<std::string> m_entities = { "Cube-1",  };
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



