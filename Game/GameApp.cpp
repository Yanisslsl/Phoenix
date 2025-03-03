#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Entities\include\Knight.h"
#include "Entities/include/Mob.h"
#include "Entities/include/Room.h"
#include "Utils/UUID.h"
#include "Core/ECSExtended/include/EntitySubsystem.h"
#include "Core/Input/include/Input.h"
#include "ECSExtended/include/TransformSubsytem.h"
#include "Maths/Noise/include/PerlinNoise.h"
#include "Editor/include/ImGuiOpenGL.h"
#include "imgui_internal.h"
#include <btBulletDynamicsCommon.h>
#include <iostream>


class PlaygroundLayer : public Phoenix::Layer
{
public:

	void CreateRandomCube() {
		// Setup random number generator
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> distribution(-2.5f, 2.5f);
    
		// Fixed height for all cubes
		const float fixedHeight = 10.0f;
    
		// Create cubes in a loop
			// Generate random X and Z positions between -2.5 and 2.5
		float randomX = distribution(gen);
		float randomZ = distribution(gen);

		std::vector<std::string> prefixes = {
			"Cube", "Box", "Block", "Crate", "Square", "Brick", "Chunk", "Dice", 
			"Prism", "Cell", "Cuboid", "Hexahedron", "Container", "Package"
		};
    
		std::vector<std::string> suffixes = {
			"Alpha", "Beta", "Delta", "Gamma", "Omega", "Prime", "X", "Y", "Z",
			"One", "Two", "Three", "Blue", "Red", "Green", "Gold", "Silver"
		};

		std::uniform_int_distribution<int> prefixDist(0, prefixes.size() - 1);
		std::uniform_int_distribution<int> suffixDist(0, suffixes.size() - 1);
		std::uniform_int_distribution<int> numberDist(1, 999);
		std::string randomName = prefixes[prefixDist(gen)] + "_" + 
							suffixes[suffixDist(gen)] + "_" + 
							std::to_string(numberDist(gen));
    
		// Create the cube entity
		auto cube = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(randomName, true);
    
		// Add sprite component
		cube->AddComponent(Phoenix::SpriteComponent("ressources/container.jpg", Phoenix::SpriteType::Cube));
    
		// Add transform component with random position
		cube->AddComponent(Phoenix::TransformComponent{
			glm::vec3(randomX, fixedHeight, randomZ),  // Random X, fixed Y, random Z
			0,                                         // No rotation
			glm::vec3(1, 1, 1)                         // Default scale
		});
    
		// Add rigidbody component
		cube->AddComponent(Phoenix::RigidBody{
			1.0f,                                      // Mass
			Phoenix::RigidbodyType::DYNAMIC            // Dynamic body type
		});
    
		// Add delay between cube creation
	}
	
	PlaygroundLayer(Phoenix::Application* app = nullptr)
		: Layer("PlaygroundLayer")
	{
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->Create3DScene("MainLevel");
  
		auto cube1 = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity("Cube2", true);
		cube1->AddComponent(Phoenix::SpriteComponent("ressources/wall.png", Phoenix::SpriteType::Cube ));
		cube1->AddComponent(Phoenix::TransformComponent{ glm::vec3(0,-1,0), 0, glm::vec3( 10,1,10)});
		cube1->AddComponent(Phoenix::RigidBody{ 1.0f,  Phoenix::RigidbodyType::STATIC });


		Phoenix::Application::Get().GetSubSystem<Phoenix::InputActionRegistratorSubSystem>()->RegisterAction(Phoenix::InputAction("CreateRandomCube", Phoenix::Key::Space), [this]() {
			this->CreateRandomCube();
		});


		
	
	}

	~PlaygroundLayer()
	{
	}

	void OnEvent(Phoenix::Event& event) override
	{
	
	}

	void OnUpdate() override
	{
		Phoenix::Timer::Update();
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
}

private:
	std::vector<std::string> m_entities = { };
	btDiscreteDynamicsWorld* m_dynamicsWorld;
	Phoenix::Ref<Phoenix::Entity> cube;
	btRigidBody* bodyCube;
	bool isDemoStarted = true;
	float m_simulationTimer = 0.0f;
	const float m_simulationRate = 0.02f;
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

Phoenix::Application* Phoenix::CreateApplication(int argc, char** argv)
{
	return new Playground();
}


