#include <future>
#include <iostream>
#include <queue>
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


class PlaygroundLayer : public Phoenix::Layer
{
public:

	int CHUNK_RATIO = 20;

	struct ChunkMesh
	{
		std::vector<float> vertices;
		std::vector<uint32_t> indices;
	};

	struct ChunkData
	{
		std::string name;
		glm::vec2 bottomLeft;
		glm::vec3 position;
		std::future<ChunkMesh*> future;

		ChunkData(std::string name, glm::vec2 bottomLeft, glm::vec3 position, std::future<ChunkMesh*> future)
			: name(name), bottomLeft(bottomLeft), position(position), future(std::move(future))
		{
		}
	};
	
	PlaygroundLayer(Phoenix::Application* app = nullptr)
		: Layer("PlaygroundLayer")
	{
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->Create3DScene("MainLevel");
		LoadChunkNeighboors();
	}

	~PlaygroundLayer()
	{
	}

	void GenerateTerrain()
	{
		
	}
	void OnUpdate() override
	{
		Phoenix::Timer::Update();
		ChunkPulling();
		CheckCurrentPosition();
		Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->OnUpdate();
	}


	void CreateChunk(std::string name, glm::vec2 bottomLeft, glm::vec3 position)
	{
		for(auto chunk : m_chunks)
		{
			if(chunk->name == name)
			{
				std::cout << "Chunk " << name << " already exists" << std::endl;
				return;
			}
		}
		std::promise<ChunkMesh*> p = std::promise<ChunkMesh*>();
		std::future<ChunkMesh*> f = p.get_future();
		std::thread t1(&PlaygroundLayer::GenerateChunk, this, std::move(p), name, bottomLeft);
		t1.detach();
		auto chunkData = new ChunkData(name, bottomLeft, position, std::move(f));
		m_pending_chunks.push_back(chunkData);
		// RemoveUnseenChunks();
	}


	void CheckCurrentPosition()
	{
		auto cameraPosition = Phoenix::Application::Get().GetSubSystem<Phoenix::SceneManagerSubSystem>()->GetActiveScene()->GetCameraController()->GetCamera().GetPosition();
		if(m_CurrentChunk == nullptr || cameraPosition.x <= m_CurrentChunk->bottomLeft.x || cameraPosition.x >= m_CurrentChunk->bottomLeft.x + 2000/CHUNK_RATIO || cameraPosition.z <= m_CurrentChunk->bottomLeft.y || cameraPosition.z >= m_CurrentChunk->bottomLeft.y + 2000/CHUNK_RATIO)
		{
			for(auto chunk : m_chunks)
			{
				if(cameraPosition.x > chunk->bottomLeft.x && cameraPosition.x < chunk->bottomLeft.x + 2000/CHUNK_RATIO && cameraPosition.z > chunk->bottomLeft.y && cameraPosition.z < chunk->bottomLeft.y + 2000/CHUNK_RATIO)
				{
					auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(chunk->name);
					if(entity)
					{
						m_CurrentChunk = chunk;
						LoadChunkNeighboors(glm::vec3(chunk->position.x, 0, chunk->position.z));
					}
					break;
				}
			}
		}
	}


	void ChunkPulling()
	{
		for(auto it = m_pending_chunks.begin(); it != m_pending_chunks.end();)
		{
			auto pendingChunk = *it;
			if(pendingChunk->future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
			{
				auto _chunk = pendingChunk->future.get();
				Phoenix::Ref<Phoenix::Entity> chunk = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->CreateEntity(pendingChunk->name, true);
				chunk->AddComponent(Phoenix::SpriteComponent(Phoenix::SpriteType::Custom, "ressources/terrain-grass.jpg", _chunk->vertices, _chunk->indices ));
				chunk->AddComponent(Phoenix::TransformComponent{ glm::vec3(pendingChunk->position.x, -10, pendingChunk->position.z), 0, glm::vec3(1000/CHUNK_RATIO, 3,1000/CHUNK_RATIO) });
				Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(pendingChunk->name)->SetRotation(0.f, glm::vec3(1, 0, 0));
				m_chunks.push_back(pendingChunk);
				it = m_pending_chunks.erase(it);
				return;
			}else
			{
				++it;
			}
		}
	}

	void LoadChunkNeighboors(glm::vec3 center = glm::vec3(0,0,0))
	{
		const int RADIUS = 4;
		int chunkSize = 2000/CHUNK_RATIO;
		int startX = center.x - (RADIUS * chunkSize + chunkSize/2);
		int startZ = center.z - (RADIUS * chunkSize + chunkSize/2);

		std::unordered_set<std::string> chunksToKeep;

		for(int i = 0; i < 2 * RADIUS + 1; i++)
		{
			for(int j = 0; j < 2 * RADIUS + 1; j++)
			{
				auto bottomLeft = glm::vec2(startX + (j * chunkSize), startZ + (i * chunkSize));
				float centerX = bottomLeft.x + (chunkSize/2);
				float centerZ = bottomLeft.y + (chunkSize/2);
				auto position = glm::vec3(centerX, 0, centerZ);
            
				std::string chunkName = "Chunk-" + std::to_string(centerX) + "-" + std::to_string(centerZ);
				chunksToKeep.insert(chunkName);
				CreateChunk(chunkName, bottomLeft, position);
			}
		}

		std::vector<ChunkData*> chunksToRemove;
    
		for(auto chunk : m_chunks)
		{
			if(chunksToKeep.find(chunk->name) == chunksToKeep.end())
			{
				chunksToRemove.push_back(chunk);
			}
		}

		for(auto chunk : chunksToRemove)
		{
			auto entity = Phoenix::Application::Get().GetSubSystem<Phoenix::EntitySubsystem>()->GetEntityByName(chunk->name);
			if(entity)
			{
				entity->Destroy();
				m_chunks.erase(std::remove(m_chunks.begin(), m_chunks.end(), chunk), m_chunks.end());
				delete chunk;
			}
		}
	}

	void GenerateChunk(std::promise<ChunkMesh*> p, std::string name, glm::vec2 bottomLeft)
	{
		std::vector<float> vertices;
        std::vector<uint32_t> indices;

        int GRID_SIZE = 5;

		Phoenix::PerlinNoise *noise = new Phoenix::PerlinNoise();
  
        int dWidth = 2000/CHUNK_RATIO;
        int dHeight = 2000/CHUNK_RATIO;
        std::vector heights = std::vector<float>();
  
        for(int x = 0; x < dWidth; x++) {
            for(int z = 0; z < dHeight; z++) {
                float height = 0.0f;
                float frequency = 1.0f;
                float amplitude = 1.0f;
                const float lacunarity = 2.f;
                const float persistence = 0.8f;

            	float localX = (float)x / (dWidth - 1);
            	float localZ = (float)z / (dHeight - 1);

            	float px = (localX - 0.5f) * 2.0f;
            	float pz = (localZ - 0.5f) * 2.0f;

            	// Compute chunks offset from local position to world position
            	float chunkOffsetX = (bottomLeft.x / (float)dWidth) * 2.0f;
            	float chunkOffsetZ = (bottomLeft.y / (float)dHeight) * 2.0f;


                for(int i = 0; i < 4; i++)
                {
                    height += noise->Generate2D(( px + chunkOffsetX) * frequency / GRID_SIZE, (pz + chunkOffsetZ) * frequency / GRID_SIZE) * amplitude;
                    frequency *= lacunarity;
                    amplitude *= persistence;
                }
  
                if(height > 1.0f)
                    height = 1.0f;
                else if(height < -1.0f)
                    height = -1.0f;
                heights.push_back(height);
  
                vertices.push_back(px);
                vertices.push_back(height); // y (height from noise)
                vertices.push_back(pz);
                vertices.push_back(px); // textures
                vertices.push_back(pz);
            }
        }
  
		for(int x = 0; x < dWidth; x++) {
			for(int z = 0; z < dHeight; z++) {
                uint32_t topLeft = x * dHeight  + z;
                uint32_t topRight = topLeft + 1;
                uint32_t bottomLeft = (x + 1) * dHeight + z;
                uint32_t bottomRight = bottomLeft + 1;
            
                // First triangle
                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);
            
                // Second triangle
                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
            }
        }
		p.set_value(new ChunkMesh({vertices, indices }));
	}

	void OnEvent(Phoenix::Event& event) override
	{
	
	}

private:
	std::vector<std::string> m_entities = { };
	std::vector<ChunkData*> m_pending_chunks;
	std::vector<ChunkData*> m_chunks;
	ChunkData* m_CurrentChunk = nullptr;
	std::queue<ChunkData*> m_chunkQueue;
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


