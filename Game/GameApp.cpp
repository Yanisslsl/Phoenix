#include "Phoenix.h"
#include "Common/Core/Graphics/DataObjects/include/Shader.h"
#include "Common/Core/Graphics/DataObjects/include/VertexArray.h"
#include "Common/Core/Graphics/Render/include/RenderCommand.h"
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


		m_VertexArray = Phoenix::VertexArray::Create();
		float vertices[] = {
			// positions         // colors
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
			0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	   };
		auto vertexBuffer = Phoenix::VertexBuffer::Create(vertices, sizeof(vertices));
		Phoenix::BufferLayout layout = {
			{ Phoenix::ShaderDataType::Float3, "aPos" },
			{ Phoenix::ShaderDataType::Float3, "aColor" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		m_Shader = Phoenix::Shader::Create("VertexPosColor", vsSrc, fsSrc);
		m_Shader->Bind();

	}

	void OnUpdate() override
	{
		Phoenix::RenderCommand::SetClearColor({ 0.9f, 0.1f, 0.1f, 1 });
		Phoenix::RenderCommand::Clear();
		Phoenix::Renderer::Submit(m_Shader, m_VertexArray);
	}

	void OnEvent(Phoenix::Event& event) override
	{
		PX_TRACE("Event catched {0}", event.GetName());
	}
	
private:
	Phoenix::Ref<Phoenix::Shader> m_Shader;
	Phoenix::Ref<Phoenix::VertexArray> m_VertexArray;
	
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
