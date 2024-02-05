#include "Phoenix.h"
#include "Common/Core/Graphics/DataObjects/include/Shader.h"
#include "Common/Core/Graphics/DataObjects/include/Texture.h"
#include "Common/Core/Graphics/DataObjects/include/VertexArray.h"
#include "Common/Core/Graphics/Render/include/Renderer.h"


class ExampleLayer : public Phoenix::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		const char* vsSrc = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0";

		const char *fsSrc = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(ourColor, 1.0f);\n"
	"}\n\0";


		// m_VertexArray = Phoenix::VertexArray::Create();
		// m_VertexArray = Phoenix::Renderer::CreateVertexArray();

		float vertices[] = {
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		   -0.5f,  0.5f, 0.0f , 1.0f, 0.0f, 0.0f,
		};

		uint32_t indices[] = {
			0, 1, 3,
			1, 2, 3
		};
		// auto vertexBuffer = Phoenix::VertexBuffer::Create(vertices, sizeof(vertices));
		Phoenix::BufferLayout layout = {
			{ Phoenix::ShaderDataType::Float3, "aPos" },
		{ Phoenix::ShaderDataType::Float3, "aColor" }
		};
		// vertexBuffer->SetLayout(layout);
		// m_VertexArray->AddVertexBuffer(vertexBuffer);
		
		
		//
		// auto indexBuffer  = Phoenix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		// m_VertexArray->SetIndexBuffer(indexBuffer);
		// m_Texture = Phoenix::Texture2D::Create("assets/container.jpg");
		//
		// m_Shader = Phoenix::Shader::Create("VertexPosColor", vsSrc, fsSrc);
		// m_Shader->Bind();
		Phoenix::Renderer::CreateShape("rectangle", vertices, sizeof(vertices), indices , sizeof(indices),  vsSrc, fsSrc, layout);

		// Needs to first call useProgram before setting uniforms

	}

	void OnUpdate() override
	{
		Phoenix::Renderer::SetClearColor({ 1.0f, 1.0f, 0.0f, 1 });
		Phoenix::Renderer::Clear();

		Phoenix::Renderer::OnUpdate();
		// float timeValue = Phoenix::Timer::Elapsed();
		// float greenValue = (sin(timeValue) / 2.0f) + 0.5f; 
		// // Needs to first call useProgram before setting uniforms
		// m_Shader->SetFloat4("customColor", { 0.0f, greenValue, 0.0f, 1.0f });
		// m_Texture->Bind();
		// Phoenix::Renderer::Submit(m_Shader, m_VertexArray);
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
