#include "../include/Renderer.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

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
        s_ShapeData.clear();
        // Renderer3D::Shutdown();
    }

    void Renderer::BeginScene() {
        // s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
        s_RendererAPI->SetClearColor({0.1f, 0.1f, 0.1f, 1});
    }

    void Renderer::EndScene() {
    }


    // @TODO create base type maths type that encapsulates glm types
    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,Ref<Texture> texture, const glm::vec2& transform) {
        shader->SetMat4("projection", s_SceneData->ViewProjectionMatrix);
        shader->SetFloat3("customColor", {0.2f, 0.3f, 0.8f});
        shader->Bind();
        // we set the model matrix to the shader by using the transform vector with z = 1.0f for the 2D rendering
        shader->SetMat4("transform", glm::translate(glm::mat4(1.0f), glm::vec3(transform.x, transform.y, 1.0f)));
        texture->Bind();
        vertexArray->Bind();
        DrawIndexed(vertexArray);
    }

    void Renderer::CreateShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const glm::vec2& transform)
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

    void Renderer::CreateTexturedShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const char* texturePath, const glm::vec2& transform)
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

    void Renderer::UpdateShapeTransform(std::string name, const glm::vec2& transform)
    {
        s_ShapeData.find(name)->second.transform = transform;
    }
}
