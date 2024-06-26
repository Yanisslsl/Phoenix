#include "Renderer3D.h"
#include "Core/Graphics/DataObjects/include/Shader.h"


namespace Phoenix
{
    void Renderer3D::CreateQuad(std::string name,  const ColorType color, const glm::mat4 modelMat)
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
            0, 1, 5,  5, 1,  6,
            1, 2, 6,  6, 2,  7,
            2, 3, 7,  7, 3,  8,
            3, 4, 8,  8, 4,  9,
            10, 11, 0,  0,11, 1,
            5, 6,12, 12, 6,  13
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
}