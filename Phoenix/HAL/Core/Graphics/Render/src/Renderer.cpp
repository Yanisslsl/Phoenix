#include "../include/Renderer.h"

#include <glm/ext/matrix_transform.hpp>
#include "Utils/Color.h"
#include "Utils/Timer.h"
#include "Core/Graphics/DataObjects/include/Shader.h"


namespace Phoenix
{
    // Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
    // Scope<RendererAPI> Renderer::s_RendererAPI = RendererAPI::Create();
    // std::map<std::string, ShapeData> Renderer::s_ShapeData = std::map<std::string, ShapeData>();

    Renderer::Renderer()
    {
        s_SceneData = CreateScope<SceneData>();
        s_RendererAPI = RendererAPI::Create();
        s_ShapeData = std::map<std::string, ShapeData>();
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::Init()
    {
        s_RendererAPI->Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        s_RendererAPI->SetViewport(0, 0, width, height);
    }

    void Renderer::SetClearColor(const ColorRGBA color)
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

    void Renderer::Shutdown()
    {
        s_ShapeData.clear();
    }

    void Renderer::BeginScene()
    {
        s_RendererAPI->SetClearColor({0., 0., 0., 1});
    }

    void Renderer::EndScene()
    {
    }
    
    // @TODO create base type maths type that encapsulates glm types
    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, Ref<Texture> texture, ColorType color,
                          const glm::mat4 modelMat, TextureData textureData)
    {
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetFloat3("u_Color", {0.2f, 0.3f, 0.8f});
        shader->Bind();
        // we set the model matrix to the shader by using the transform vector with z = 1.0f for the 2D rendering
        shader->SetMat4("u_Model", modelMat);

        if(texture != nullptr && !textureData.isEnable)
        {
            texture->Bind();
            shader->SetFloat3("u_Color", glm::vec3(0.0f, 0.0f, 0.0f));
        }
        else if(textureData.isEnable)
        {
            textureData.textures[textureData.currentTextureIndex]->Bind();
            shader->SetFloat3("u_Color", glm::vec3(0.0f, 0.0f, 0.0f));
        }
        else
        {
            shader->SetFloat3("u_Color", color);
        }
        vertexArray->Bind();
        DrawIndexed(vertexArray);
    }

    void Renderer::CreateShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices,
                               const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout,
                               const glm::mat4 modelMat)
    {
        Ref<VertexArray> vertexArray = s_RendererAPI->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = s_RendererAPI->CreateVertexBuffer(vertices);
        vertexBuffer->SetLayout(bufferlayout);
        vertexArray->AddVertexBuffer(vertexBuffer);
        Ref<IndexBuffer> indexBuffer = s_RendererAPI->CreateIndexBuffer(indices);
        vertexArray->SetIndexBuffer(indexBuffer);
        Ref<Shader> shader = s_RendererAPI->CreateShader(name, vertexShader, fragmentShader);
        shader->Bind();
        s_ShapeData.insert(std::pair<std::string, ShapeData>(name, {
                                                                 vertexBuffer, indexBuffer, vertexArray, shader,
                                                                 bufferlayout, modelMat
                                                             }));
    }

    void Renderer::CreateTexturedShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices,
                                       const char* vertexShader, const char* fragmentShader,
                                       const BufferLayout bufferlayout, const char* texturePath,
                                       const glm::mat4 modelMat)
    {
        Ref<VertexArray> vertexArray = s_RendererAPI->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = s_RendererAPI->CreateVertexBuffer(vertices);
        vertexBuffer->SetLayout(bufferlayout);
        vertexArray->AddVertexBuffer(vertexBuffer);
        Ref<IndexBuffer> indexBuffer = s_RendererAPI->CreateIndexBuffer(indices);
        vertexArray->SetIndexBuffer(indexBuffer);
        Ref<Texture2D> texture = s_RendererAPI->CreateTexture2D(texturePath);
        Ref<Shader> shader = s_RendererAPI->CreateShader(name, vertexShader, fragmentShader);
        shader->Bind();
        shader->SetInt("u_Texture", 0);
        ShapeData shape = ShapeData{
            vertexBuffer, indexBuffer, vertexArray, shader,
            bufferlayout, modelMat 
        };
        shape.texture = texture;
        s_ShapeData.insert(std::pair<std::string, ShapeData>(name, shape));
    }

    void Renderer::CreateQuad(std::string name, const char* texturePath, const glm::mat4 modelMat)
    {
        std::vector<float> vertices = {
            0.5f,  0.5f, 0.0f,1.0f, 1.0f,   // top right
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
               -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
               -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  
        };
		
        std::vector<uint32_t> indices = {
            0, 1, 3,
            1, 2, 3
        };
        Phoenix::BufferLayout layout = {
            { Phoenix::ShaderDataType::Float3, "aPos" },
                    { Phoenix::ShaderDataType::Float2, "aTexCoord" }
        };
        Ref<VertexArray> vertexArray = s_RendererAPI->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = s_RendererAPI->CreateVertexBuffer(vertices);
        vertexBuffer->SetLayout(layout);
        vertexArray->AddVertexBuffer(vertexBuffer);
        Ref<IndexBuffer> indexBuffer = s_RendererAPI->CreateIndexBuffer(indices);
        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
        Ref<Texture2D> texture = s_RendererAPI->CreateTexture2D(texturePath);
        Ref<Shader> shader = s_RendererAPI->CreateShader(name);
        shader->Bind();
        shader->SetInt("u_Texture", 0);
        ShapeData shape = ShapeData{
            vertexBuffer, indexBuffer, vertexArray, shader,
            layout, modelMat 
        };
        shape.texture = texture;
        s_ShapeData.insert(std::pair<std::string, ShapeData>(name, shape));
    }

    void Renderer::CreateQuad(std::string name, const ColorType color , const glm::mat4 modelMat)
    {
        std::vector<float> vertices = {
            0.5f,  0.5f, 0.0f,1.0f, 1.0f,   // top right
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
               -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
               -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  
        };
		
        std::vector<uint32_t> indices = {
            0, 1, 3,
            1, 2, 3
        };
        BufferLayout layout = {
            { ShaderDataType::Float3, "aPos" },
                    { ShaderDataType::Float2, "aTexCoord" }
        };
        Ref<VertexArray> vertexArray = s_RendererAPI->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = s_RendererAPI->CreateVertexBuffer(vertices);
        vertexBuffer->SetLayout(layout);
        vertexArray->AddVertexBuffer(vertexBuffer);
        Ref<IndexBuffer> indexBuffer = s_RendererAPI->CreateIndexBuffer(indices);
        vertexArray->AddVertexBuffer(vertexBuffer);
        vertexArray->SetIndexBuffer(indexBuffer);
        Ref<Shader> shader = s_RendererAPI->CreateShader(name);
        shader->Bind();
        shader->SetInt("u_Texture", 0);
        ShapeData shape = ShapeData{
            vertexBuffer, indexBuffer, vertexArray, shader,
            layout, modelMat 
        };
        shape.color = color;
        s_ShapeData.insert(std::pair<std::string, ShapeData>(name, shape));
    }

    void Renderer::SetTexturesPaths(std::string shapeName, std::string name, std::vector<std::string> texturesPaths)
    {
        std::vector<Ref<Texture2D>> textures;
        for(auto texturePath : texturesPaths)
        {
            Ref<Texture2D> texture = s_RendererAPI->CreateTexture2D(texturePath);
            textures.push_back(texture);
        }
        if(s_ShapeData.find(shapeName) == s_ShapeData.end())
        {
            PX_ERROR("Shape not found");
            return;
        }
        TextureData textureData = TextureData{textures, false, 0};
        s_ShapeData.find(shapeName)->second.texturesDatas[name] = textureData;
    }

    void Renderer::DeleteShape(std::string name)
    {
        auto u = s_ShapeData;
        s_ShapeData.erase(name);
    }


    Ref<Shader> Renderer::GetShader(std::string name)
    {
        return s_ShapeData.find(name)->second.shader;
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }


    // enable texture data
    void Renderer::SetTextureIndex(std::string shapeName, int textureIndex)
    {
        if(s_ShapeData.find(shapeName) == s_ShapeData.end())
        {
            PX_ERROR("Shape not found");
            return;
        }
        s_ShapeData.find(shapeName)->second.currentTextureData.currentTextureIndex = textureIndex;
    }

    void Renderer::EnableShapeTexture(std::string shapeName, std::string name)
    {
        if(s_ShapeData.find(shapeName) == s_ShapeData.end())
        {
            PX_ERROR("Shape not found");
            return;
        }
        s_ShapeData.find(shapeName)->second.EnableTextureData(name);
    }

    void Renderer::OnUpdate()
    {
        for(auto& shape : s_ShapeData)
        {
            Submit(shape.second.shader, shape.second.vertexArray, shape.second.texture, shape.second.color, shape.second.modelMat, shape.second.currentTextureData);
        }
    }   

    void Renderer::UpdateModelMatrix(std::string name, glm::mat4 modelMat)
    {
        if(s_ShapeData.find(name) == s_ShapeData.end())
        {
            PX_ERROR("Shape not found");
            return;
        }
        s_ShapeData.find(name)->second.modelMat = modelMat;
    }
}
