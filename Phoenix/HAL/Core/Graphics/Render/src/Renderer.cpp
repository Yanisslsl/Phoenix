#include "../include/Renderer.h"

#include <glm/ext/matrix_transform.hpp>
#include "Utils/Color.h"
#include "Utils/Timer.h"
#include "Core/Graphics/DataObjects/include/Shader.h"
#include "Maths/Noise/include/PerlinNoise.h"


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
                          const glm::mat4 modelMat, TextureData textureData, DrawType drawType)
    {
        if(shader == nullptr || vertexArray == nullptr)
        {
            PX_ERROR("Shader or VertexArray is null");
            return;
        }
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetFloat3("u_Color", {0.2f, 0.3f, 0.8f});
        shader->Bind();
        // we set the model matrix to the shader by using the transform vector with z = 1.0f for the 2D rendering
        shader->SetMat4("u_Model", modelMat);
        
        // for shapes with textures but no animation
        if(texture != nullptr && !textureData.isEnable)
        {
            texture->Bind();
            shader->SetFloat3("u_Color", glm::vec3(0.0f, 0.0f, 0.0f));
        }
        // for shapes with animation
        else if(textureData.isEnable)
        {
            textureData.textures[textureData.currentTextureIndex]->Bind();
            shader->SetFloat3("u_Color", glm::vec3(0.0f, 0.0f, 0.0f));
        }
        // for shapes with color
        else
        {
            shader->SetFloat3("u_Color", color);
        }
        vertexArray->Bind();

        if(drawType == DrawType::LINES)
        {
            DrawLines(vertexArray, vertexArray->GetVertexCount());
            return;
        }
        
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
                                        const char* texturePath,
                                       const glm::mat4 modelMat)
    {
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
        
        Ref<Texture2D> texture;
        if(s_CachedTextures.find(texturePath) == s_CachedTextures.end())
        {
            texture = s_RendererAPI->CreateTexture2D(texturePath);
            s_CachedTextures[texturePath] = texture; 
        } else
        {
            texture = s_CachedTextures[texturePath];
        }
        
        Ref<Shader> shader;
        std::string defaultShader = "DEFAULT_SHADER"; //@TODO: constant for now, make it dynamic when we have a shader manager
        if(s_CachedShaders.find(defaultShader) == s_CachedShaders.end())
        {
            shader = s_RendererAPI->CreateShader(defaultShader);
            s_CachedShaders[defaultShader] = shader;
        } else
        {
            shader = s_CachedShaders[defaultShader];
        }
        
        shader->Bind();
        shader->SetInt("u_Texture", 0);
        ShapeData shape = ShapeData{
            vertexBuffer, indexBuffer, vertexArray, shader,
            layout, modelMat 
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

    void Renderer::CreateCube(std::string name, const char* texturePath, const glm::mat4 modelMat)
    {
            std::vector<float> vertices {
                -1,-1,-1, 0, 0,
                 1,-1,-1, 1, 0,
                 1, 1,-1, 2, 0,
                -1, 1,-1, 3, 0,
                -1,-1,-1, 4, 0,
        
                -1,-1, 1, 0, 1,
                 1,-1, 1, 1, 1,
                 1, 1, 1, 2, 1,
                -1, 1, 1, 3, 1,
                -1,-1, 1, 4, 1,
        
                -1, 1,-1, 0,-1,
                 1, 1,-1, 1,-1,
        
                -1, 1, 1, 0, 2,
                 1, 1, 1, 1, 2
            };
            std::vector<uint32_t> indices =  {
                0, 1, 5,  5, 1, 6,
                1, 2, 6,  6, 2, 7,
                2, 3, 7,  7, 3, 8,
                3, 4, 8,  8, 4, 9,
               10,11, 0,  0,11, 1,
                5, 6,12, 12, 6,13
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


    void Renderer::CreatePlane(std::string name, const char* texturePath, const glm::mat4 modelMat)
    {
        std::vector<float> vertices = {
            // positions          // texture coords
            -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,  // 0
             0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  // 1
             0.5f,  0.5f,  0.0f,  1.0f, 1.0f,  // 2
            -0.5f,  0.5f,  0.0f,  0.0f, 1.0f   // 3
        };

        std::vector<uint32_t> indices = {
            0, 1, 2,    // first triangle
            2, 3, 0     // second triangle
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

    void Renderer::CreatePlane(std::string name, ColorType color, const glm::mat4 modelMat)
    {
        std::vector<float> vertices = {
            // positions          // texture coords
            -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,  // 0
             0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  // 1
             0.5f,  0.5f,  0.0f,  1.0f, 1.0f,  // 2
            -0.5f,  0.5f,  0.0f,  0.0f, 1.0f   // 3
        };

        std::vector<uint32_t> indices = {
            0, 1, 2,    // first triangle
            2, 3, 0     // second triangle
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

    void Renderer::CreateTerrain(std::string name, const char* texturePath, const glm::mat4 modelMat, int gridSize)
    {
        std::vector<float> vertices;
        std::vector<uint32_t> indices;

        int GRID_SIZE = 1;

        PerlinNoise *noise = new PerlinNoise();

        int dWidth = 100;
        int dHeight = 100;
        std::vector heights = std::vector<float>();

        // Generate a grid of vertices
        for(int z = 0; z < dWidth; z++) {
            for(int x = 0; x < dHeight; x++) {
                float height = 0.0f;
                float frequency = 1.0f;
                float amplitude = 1.0f;
                const float lacunarity = 4.f;   // Augmentation de la fréquence entre octaves
                const float persistence = 0.8f; 

                // Calculate normalized position (0 to 1)
                float nx = (float)x / (dWidth - 1);
                float nz = (float)z / (dHeight - 1);
            
                float px = (nx - 0.5f) * 2.0f;  // Donne des coordonnées de -1 à 1
                float pz = (nz - 0.5f) * 2.0f;

                for(int i = 0; i < 8; i++)
                {
                    height += noise->Generate2D(px * frequency / GRID_SIZE, pz * frequency / GRID_SIZE) * amplitude;
                    frequency *= lacunarity;
                    amplitude *= persistence;
                }

                if(height > 1.0f)
                    height = 1.0f;
                else if(height < -1.0f)
                    height = -1.0f;
                // height *= .f;
                heights.push_back(height);

                vertices.push_back(px);          // x
                vertices.push_back(height);      // y (height from noise)
                vertices.push_back(pz);          // z
                vertices.push_back(nx);          // texture u
                vertices.push_back(nz);          // texture v
            }
        }

        // Generate indices for triangles
        for(int z = 0; z < dWidth - 1; z++) {
            for(int x = 0; x < dHeight - 1; x++) {
                uint32_t topLeft = z * dWidth + x;
                uint32_t topRight = topLeft + 1;
                uint32_t bottomLeft = (z + 1) * dHeight + x;
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

        BufferLayout layout = {
            { ShaderDataType::Float3, "aPos" },
            { ShaderDataType::Float2, "aTexCoord" }
        };

        Ref<VertexArray> vertexArray = s_RendererAPI->CreateVertexArray();
        Ref<VertexBuffer> vertexBuffer = s_RendererAPI->CreateVertexBuffer(vertices);
        vertexBuffer->SetLayout(layout);
        vertexArray->AddVertexBuffer(vertexBuffer);
    
        Ref<IndexBuffer> indexBuffer = s_RendererAPI->CreateIndexBuffer(indices);
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

    void Renderer::CreateCube(std::string name, ColorType color, const glm::mat4 modelMat)
    {
         std::vector<float> vertices {
            -1,-1,-1, 0, 0,
             1,-1,-1, 1, 0,
             1, 1,-1, 2, 0,
            -1, 1,-1, 3, 0,
            -1,-1,-1, 4, 0,
    
            -1,-1, 1, 0, 1,
             1,-1, 1, 1, 1,
             1, 1, 1, 2, 1,
            -1, 1, 1, 3, 1,
            -1,-1, 1, 4, 1,
    
            -1, 1,-1, 0,-1,
             1, 1,-1, 1,-1,
    
            -1, 1, 1, 0, 2,
             1, 1, 1, 1, 2
        };
        std::vector<uint32_t> indices =  {
            0, 1, 5,  5, 1, 6,
            1, 2, 6,  6, 2, 7,
            2, 3, 7,  7, 3, 8,
            3, 4, 8,  8, 4, 9,
           10,11, 0,  0,11, 1,
            5, 6,12, 12, 6,13
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

    void Renderer::DeleteShape(std::string name)
    {
        s_ShapeData.erase(name);
    }


    Ref<Shader> Renderer::GetShader(std::string name)
    {
        return s_ShapeData.find(name)->second.shader;
    }

    void Renderer::BeginScene(Camera& camera)
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
            Submit(shape.second.shader, shape.second.vertexArray, shape.second.texture, shape.second.color, shape.second.modelMat, shape.second.currentTextureData, shape.second.drawType);
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

    void Renderer::UpdateShapeColor(std::string name, ColorType color)
    {
        if(s_ShapeData.find(name) == s_ShapeData.end())
        {
            PX_ERROR("Shape not found");
            return;
        }
        s_ShapeData.find(name)->second.color = color;
    }

    void Renderer::DrawLine(std::string& name, const glm::vec3& start, const glm::vec3& end, const glm::vec3& color, float width)
    {
        std::vector<float> vertices = {
            start.x, start.y, start.z, 0.0f, 0.0f,
            end.x, end.y, end.z, 1.0f, 1.0f       
        };

        Ref<VertexArray> lineVA = s_RendererAPI->CreateVertexArray();
    
        Ref<VertexBuffer> lineVB = s_RendererAPI->CreateVertexBuffer(vertices);
    
        BufferLayout layout = {
            { ShaderDataType::Float3, "aPos" },
            { ShaderDataType::Float2, "aTexCoord" }
        };
        lineVB->SetLayout(layout);
        lineVA->AddVertexBuffer(lineVB);
        lineVA->SetVertexCount(2);
    
        Ref<Shader> lineShader;
        std::string defaultShader = "DEFAULT_SHADER_LINE"; //@TODO: constant for now, make it dynamic when we have a shader manager
        if(s_CachedShaders.find(defaultShader) == s_CachedShaders.end())
        {
            lineShader = s_RendererAPI->CreateShader(defaultShader);
            s_CachedShaders[defaultShader] = lineShader;
        } else
        {
            lineShader = s_CachedShaders[defaultShader];
        }
        
        s_RendererAPI->SetLineWidth(width);
        
        glm::mat4 modelMatrix = glm::mat4(1.0f); // Matrice identité
        
        // lineShader->Bind();
        lineShader->SetInt("u_Texture", 0);
        
        auto shape = ShapeData{
            lineVB, nullptr, lineVA, lineShader,
            layout, modelMatrix
        };
        shape.color = color;
        shape.vertexCount = 2;
        shape.drawType = LINES;
        s_ShapeData.insert(std::pair<std::string, ShapeData>(name, shape));
    }
}
