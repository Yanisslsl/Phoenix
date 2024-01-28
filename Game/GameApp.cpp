#include "Phoenix.h"
#include "Common/Core/Graphics/DataObjects/include/Shader.h"
#include "Common/Core/Graphics/DataObjects/include/Texture.h"
#include "Common/Core/Graphics/DataObjects/include/VertexArray.h"
#include "Common/Core/Graphics/Render/include/RenderCommand.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"


class ExampleLayer : public Phoenix::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		const char* vsSrc2 = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;
		layout (location = 2) in vec2 aTexCoord;

		out vec3 ourColor;
		out vec2 TexCoord;

		void main()
		{
		    gl_Position = vec4(aPos, 1.0);
		    ourColor = aColor;
		    TexCoord = aTexCoord;
		}
		)";

		const char* fsSrc2 = R"(
			#version 330 core
			out vec4 FragColor;
			  
			in vec3 ourColor;
			in vec2 TexCoord;

			uniform sampler2D ourTexture;

			void main()
			{
			FragColor = texture(ourTexture, TexCoord);
			}
		)";


		m_VertexArray = Phoenix::VertexArray::Create();
		float vertices[] = {
			// positions          // colors           // texture coords
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	   };
		unsigned int indices[] = {  // Notons que l’on commence à 0!
			0, 1, 3,   // premier triangle
			1, 2, 3    // second triangle
		};
		auto vertexBuffer = Phoenix::VertexBuffer::Create(vertices, sizeof(vertices));
		Phoenix::BufferLayout layout = {
			{ Phoenix::ShaderDataType::Float3, "aPos" },
			{ Phoenix::ShaderDataType::Float3, "aColor" },
			{ Phoenix::ShaderDataType::Float2, "aTexCoord" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);



		auto indexBuffer  = Phoenix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_Texture = Phoenix::Texture2D::Create("assets/container.jpg");

		m_Shader = Phoenix::Shader::Create("VertexPosColor", vsSrc2, fsSrc2);
		m_Shader->Bind();

		// Needs to first call useProgram before setting uniforms

	}

	void OnUpdate() override
	{
		Phoenix::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		Phoenix::RenderCommand::Clear();

		m_Shader->Bind();
		float timeValue = Phoenix::Timer::Elapsed();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f; 
		// Needs to first call useProgram before setting uniforms
		m_Shader->SetFloat4("customColor", { 0.0f, greenValue, 0.0f, 1.0f });
		m_Texture->Bind();
		Phoenix::Renderer::Submit(m_Shader, m_VertexArray);
	}

	void OnEvent(Phoenix::Event& event) override
	{
		PX_TRACE("Event catched {0}", event.GetName());
	}









	
private:
	Phoenix::Ref<Phoenix::Shader> m_Shader;
	Phoenix::Ref<Phoenix::VertexArray> m_VertexArray;
	Phoenix::Ref<Phoenix::Texture2D> m_Texture;
};

class GameApp : public Phoenix::Application
{
public:
	GameApp()
	{
		PushLayer(new ExampleLayer());
	}

	~GameApp()
	{

	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new GameApp();
}
