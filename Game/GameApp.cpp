#include <glm/ext/matrix_transform.hpp>
#include "Phoenix.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"
#include "Common/Core/Scene/include/OrthographicCameraController.h"
#include "Common/Core/Scene/include/Scene.h"

class ExampleLayer : public Phoenix::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		const char* vsSrc = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;

		uniform mat4 u_ViewProjection;
		uniform vec3 customColor;
		uniform mat4 projection;
		uniform mat4 transform;

		out vec3 ourColor;
		out vec2 TexCoord;

		void main()
		{
			gl_Position = projection * transform * vec4(aPos, 1.0);
		    ourColor = customColor;
		}
		)";

		const char* fsSrc = R"(
			#version 330 core
			out vec4 FragColor;
			  
			in vec3 ourColor;

			uniform sampler2D ourTexture;

			void main()
			{
			FragColor = vec4(ourColor, 1.0);
			}
		)";

		float scaleFactor = 100.0f;
		std::vector<float> vertices = {
			0.5f * scaleFactor,  0.5f * scaleFactor, 0.0f * scaleFactor,   1.0f , 0.0f, 0.0f,   1.0f, 1.0f,   // top right
				0.5f * scaleFactor, -0.5f * scaleFactor, 0.0f * scaleFactor,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			   -0.5f * scaleFactor, -0.5f * scaleFactor, 0.0f * scaleFactor,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			   -0.5f * scaleFactor,  0.5f * scaleFactor, 0.0f * scaleFactor,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  
		};
		std::vector<uint32_t> indices = {
			0, 1, 3,
			1, 2, 3
		};
		Phoenix::BufferLayout layout = {
			{ Phoenix::ShaderDataType::Float3, "aPos" },
					{ Phoenix::ShaderDataType::Float3, "aColor" },
					{ Phoenix::ShaderDataType::Float2, "aTexCoord" }
		};
		
		Phoenix::OrthographicCameraController cameraController = Phoenix::OrthographicCameraController(0.0f, 1280.0f, 0.0f, 720.0f, 1.0f, false);
		m_Scene = new Phoenix::Scene(cameraController);
		Phoenix::Entity* square = m_Scene->CreateEntity("square");
		square->AddComponent<Phoenix::SpriteComponent>(Phoenix::SpriteComponent("square", vertices, indices, vsSrc, fsSrc, layout,"assets/container.jpg" ));
		square->AddComponent<Phoenix::TransformComponent>(Phoenix::TransformComponent(glm::vec2(980.0f/2, 720.0f/2)));

		Phoenix::Entity* square1 = m_Scene->CreateEntity("square1");
		square1->AddComponent<Phoenix::SpriteComponent>(Phoenix::SpriteComponent("square1", vertices, indices, vsSrc, fsSrc, layout,"assets/container.jpg" ));
		square1->AddComponent<Phoenix::TransformComponent>(Phoenix::TransformComponent(glm::vec2(1280.0f/2, 720.0f/2)));

		Phoenix::Entity* square2 = m_Scene->CreateEntity("square2");
		square2->AddComponent<Phoenix::SpriteComponent>(Phoenix::SpriteComponent("square2", vertices, indices, vsSrc, fsSrc, layout,"assets/container.jpg" ));
		square2->AddComponent<Phoenix::TransformComponent>(Phoenix::TransformComponent(glm::vec2(1580.0f/2, 720.0f/2)));
	}

	void OnUpdate() override
	{
		m_Scene->OnUpdate();
	}
	
	//
	// void OnEvent(Phoenix::Event& event) override
	// {
	// 	m_CameraController.OnEvent(event);
	// 	PX_TRACE("Event catched {0}", event.GetName());
	// }
	
private:
	Phoenix::Scene* m_Scene;
};
class GameApp : public Phoenix::Application
{
public:
	GameApp()
	{
		PushLayer(new ExampleLayer());
		this->GetWindow();
	}

	~GameApp()
	{

	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new GameApp();
}
