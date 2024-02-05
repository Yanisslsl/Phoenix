#include "../include/Renderer.h"

namespace Phoenix {
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
    Scope<RendererAPI> Renderer::s_RendererAPI = RendererAPI::Create();
    std::map<std::string, ShapeData> Renderer::s_ShapeData = std::map<std::string, ShapeData>();
    Ref<VertexArray> Renderer::m_Vertex_Array;
    Ref<Shader> Renderer::m_Shader;

    void Renderer::Shutdown() {
        //@TODO add Renderer 3D
        // Renderer3D::Shutdown();
    }

    void Renderer::BeginScene() {
        // s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
        s_RendererAPI->SetClearColor({0.1f, 0.1f, 0.1f, 1});
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Maths::Matrix4& transform) {
        shader->Bind();
        // shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        // shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();
        Renderer::DrawIndexed(vertexArray);
    }

    void Renderer::CreateShape(std::string name, float* vertices, uint32_t vertices_size, uint32_t* indices, uint32_t indices_size, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const Maths::Matrix4& transform)
    {
        Ref<VertexArray> vertexArray = s_RendererAPI->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = s_RendererAPI->CreateVertexBuffer(vertices, vertices_size);
        vertexBuffer->SetLayout(bufferlayout);
        vertexArray->AddVertexBuffer(vertexBuffer);
        Ref<IndexBuffer> indexBuffer = s_RendererAPI->CreateIndexBuffer(indices, indices_size / sizeof(uint32_t));
        vertexArray->SetIndexBuffer(indexBuffer);
        Ref<Shader> shader  = s_RendererAPI->CreateShader(name, vertexShader, fragmentShader);
        shader->Bind();
        s_ShapeData.insert(std::pair<std::string, ShapeData>(name, {vertexBuffer, indexBuffer, vertexArray, shader, bufferlayout, transform}));
    }

    Ref<Shader> Renderer::GetShader(std::string name)
    {
        return s_ShapeData.find(name)->second.shader;
    }

    void Renderer::OnUpdate()
    {
        for (auto& shape : s_ShapeData)
        {
            Submit(shape.second.shader, shape.second.vertexArray, shape.second.transform);
        }
    }

    
}
