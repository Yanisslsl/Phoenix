#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Common/Core/Scene/include/Scene.h"
// #include "Common/Core/Serialization/include/BlobSerializer.h"
#include "Entities\include\Knight.h"
#include "Entities/include/Mob.h"
#include "Entities/include/Room.h"
#include "Utils/UUID.h"

class MainLayer : public Phoenix::Layer
{
public:
	MainLayer(Phoenix::Application* app = nullptr)
		: Layer("MainLayer")
	{
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->CreateScene("MainLevel");
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->SaveScene("MainLevel");
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->LoadScene("MainLevel");

		// Phoenix::Ref<Phoenix::Entity> entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Knight");
		// auto serializer = Phoenix::BlobSerializer();
		// entity->Serialize(serializer);
		// Phoenix::Ref<Phoenix::Entity> entity1 = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Knight");
		// entity1->Deserialize(serializer);
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
		new Mob(glm::vec2(500, 500));
	}

	void OnUpdate() override
	{
		// for(auto id: m_Ids)
		// {
		// 	auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(id);
		// 	auto position = entity->GetTransformPosition();
		// 	entity->SetTransformPosition(glm::vec2(position.x + 1, position.y + 1));
		// }
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
	}
	
	void OnEvent(Phoenix::Event& event) override
	{
		// m_CameraController.OnEvent(event);
		// PX_TRACE("Event catched {0}", event.GetName());
	}
	
private:
	Knight* m_player;
	std::vector<Mob*> m_mobs;
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
