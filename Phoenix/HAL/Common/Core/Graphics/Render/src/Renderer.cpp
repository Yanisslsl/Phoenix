#include "../include/Renderer.h"

namespace Phoenix {
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
    Scope<RendererAPI> Renderer::s_RendererAPI = RendererAPI::Create();
    std::map<std::string, ShapeData> Renderer::s_ShapeData = std::map<std::string, ShapeData>();

    void Renderer::Init()
    {
        s_RendererAPI->Init();
    }
    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        s_RendererAPI->SetViewport(0, 0, width, height);
    }

    void Renderer::SetClearColor(const Maths::Color color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    void Renderer::Clear()
    {
        s_RendererAPI->Clear();
    }

    void Renderer::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
    {
        s_RendererAPI->DrawIndexed(vertexArray, indexCount);
    }

    void Renderer::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
    {
        s_RendererAPI->DrawLines(vertexArray, vertexCount);
    }

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

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,Ref<Texture> texture, const Maths::Matrix4& transform) {
        shader->Bind();
        // shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        // shader->SetMat4("u_Transform", transform);
        texture->Bind();
        vertexArray->Bind();
        DrawIndexed(vertexArray);
    }

    void Renderer::CreateShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const Maths::Matrix4& transform)
    {
        Ref<VertexArray> vertexArray = s_RendererAPI->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = s_RendererAPI->CreateVertexBuffer(vertices);
        vertexBuffer->SetLayout(bufferlayout);
        vertexArray->AddVertexBuffer(vertexBuffer);
        Ref<IndexBuffer> indexBuffer = s_RendererAPI->CreateIndexBuffer(indices);
        vertexArray->SetIndexBuffer(indexBuffer);
        Ref<Shader> shader  = s_RendererAPI->CreateShader(name, vertexShader, fragmentShader);
        shader->Bind();
        s_ShapeData.insert(std::pair<std::string, ShapeData>(name, {vertexBuffer, indexBuffer, vertexArray, shader, bufferlayout, transform}));
    }

    void Renderer::CreateTexturedShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const char* texturePath, const Maths::Matrix4& transform)
    {
        Ref<VertexArray> vertexArray = s_RendererAPI->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = s_RendererAPI->CreateVertexBuffer(vertices);
        vertexBuffer->SetLayout(bufferlayout);
        vertexArray->AddVertexBuffer(vertexBuffer);
        Ref<IndexBuffer> indexBuffer = s_RendererAPI->CreateIndexBuffer(indices);
        vertexArray->SetIndexBuffer(indexBuffer);
        Ref<Texture2D> texture = s_RendererAPI->CreateTexture2D(texturePath);
        Ref<Shader> shader  = s_RendererAPI->CreateShader(name, vertexShader, fragmentShader);
        shader->Bind();
        shader->SetInt("u_Texture", 0);
        s_ShapeData.insert(std::pair<std::string, ShapeData>(name, {vertexBuffer, indexBuffer, vertexArray, shader, bufferlayout, transform, texture}));
    }



    Ref<Shader> Renderer::GetShader(std::string name)
    {
        return s_ShapeData.find(name)->second.shader;
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }


    void Renderer::OnUpdate()
    {
        for (auto& shape : s_ShapeData)
        {
            Submit(shape.second.shader, shape.second.vertexArray, shape.second.texture, shape.second.transform);
        }
    }

    
}
