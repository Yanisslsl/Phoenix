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
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos, 1.0);\n"
	"}\0";

		const char *fsSrc = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 customColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = customColor;\n"
	"}\n\0";

	



		m_VertexArray = Phoenix::VertexArray::Create();
		float vertices[] = {
			0.5f,  0.5f, 0.0f, 
			0.5f, -0.5f, 0.0f,  
		   -0.5f, -0.5f, 0.0f, 
		   -0.5f,  0.5f, 0.0f , 	   };
		unsigned int indices[] = {  // Notons que l’on commence à 0!
			0, 1, 3,   // premier triangle
			1, 2, 3    // second triangle
		};
		auto vertexBuffer = Phoenix::VertexBuffer::Create(vertices, sizeof(vertices));
		Phoenix::BufferLayout layout = {
			{ Phoenix::ShaderDataType::Float3, "aPos" },
			// { Phoenix::ShaderDataType::Float3, "aColor" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);



		auto indexBuffer  = Phoenix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_Shader = Phoenix::Shader::Create("VertexPosColor", vsSrc, fsSrc);
		m_Shader->Bind();

		// Needs to first call useProgram before setting uniforms

	}

	void OnUpdate() override
	{
		Phoenix::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		Phoenix::RenderCommand::Clear();

		m_Shader->Bind();
		float timeValue = Elapsed();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f; 
		// Needs to first call useProgram before setting uniforms
		m_Shader->SetFloat4("customColor", { 0.0f, greenValue, 0.0f, 1.0f });

		Phoenix::Renderer::Submit(m_Shader, m_VertexArray);
	}

	void OnEvent(Phoenix::Event& event) override
	{
		PX_TRACE("Event catched {0}", event.GetName());
	}








	//@TODO move to time class

	void Reset()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}
	
	float Elapsed()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_StartTime).count() * 0.001f * 0.001f * 0.001f;
	}
	
	float ElapsedMillis()
	{
		return Elapsed() * 1000.0f;
	}
	
private:
	Phoenix::Ref<Phoenix::Shader> m_Shader;
	Phoenix::Ref<Phoenix::VertexArray> m_VertexArray;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
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
