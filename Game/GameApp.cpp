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
#include "imgui_internal.h"
#include <btBulletDynamicsCommon.h>
#include <iostream>

#include "Entities/include/Boid.h"
#include "Entities/include/Editor.h"
#include "Managers/include/BoidManager.h"



class PlaygroundLayer : public Phoenix::Layer
{
public:

	
	PlaygroundLayer(Phoenix::Application* app = nullptr)
		: Layer("PlaygroundLayer")
	{
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->Create3DScene("MainLevel");
		float M_PI = 3.14159265358979323846;
		float radius = 1.0f;
		int latitudeBands = 16;
		int longitudeBands = 16;
		std::vector<float> vertices;
		std::vector<uint32_t> indices;
    
		// Générer les points de la sphère
		for (int lat = 0; lat <= latitudeBands; lat++) {
			float theta = lat * M_PI / latitudeBands;
			float sinTheta = sin(theta);
			float cosTheta = cos(theta);
        
			for (int lon = 0; lon <= longitudeBands; lon++) {
				float phi = lon * 2 * M_PI / longitudeBands;
				float sinPhi = sin(phi);
				float cosPhi = cos(phi);
            
				// Coordonnées 3D du point sur la sphère (x, y, z)
				float x = cosPhi * sinTheta;
				float y = cosTheta;
				float z = sinPhi * sinTheta;
            
				// Coordonnées de texture (u, v)
				float u = 1.0f - ((float)lon / longitudeBands);
				float v = 1.0f - ((float)lat / latitudeBands);
            
				// Ajouter le point aux vertices
				vertices.push_back(x * radius);  // x
				vertices.push_back(y * radius);  // y
				vertices.push_back(z * radius);  // z
				vertices.push_back(u);           // u
				vertices.push_back(v);           // v
			}
		}
    
		// Générer les indices pour les triangles
		for (int lat = 0; lat < latitudeBands; lat++) {
			for (int lon = 0; lon < longitudeBands; lon++) {
				int first = (lat * (longitudeBands + 1)) + lon;
				int second = first + longitudeBands + 1;
            
				// Premier triangle
				indices.push_back(first);
				indices.push_back(second);
				indices.push_back(first + 1);
            
				// Second triangle
				indices.push_back(second);
				indices.push_back(second + 1);
				indices.push_back(first + 1);
			}
		}
		m_BoidManager = Phoenix::CreateRef<BoidManager>();
		m_Editor = Phoenix::CreateRef<Editor>(m_BoidManager);

	}
	~PlaygroundLayer()
	{
	}

	void OnEvent(Phoenix::Event& event) override
	{
	
	}

	void OnUpdate() override
	{
		auto dt = Phoenix::Timer::GetDeltaTime();
		Phoenix::Timer::Update();
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
		m_Editor->OnUpdate();
	}

private:
	Phoenix::Ref<BoidManager> m_BoidManager;
	Phoenix::Ref<Editor> m_Editor;
	 Phoenix::Ref<Phoenix::Entity> entity1 = nullptr;
	Phoenix::Ref<Phoenix::Entity> entity2 = nullptr;

};

class Playground : public Phoenix::Application
{
public:
	Playground(): Application(Phoenix::ApplicationMode::Wrapped, false)
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


