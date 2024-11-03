#include "Core/Graphics/ModelLoader/include/Mesh.h"

#include "Core/Application/include/Application.h"
#include "Core/Graphics/Render/include/Renderer.h"

namespace Phoenix
{
    void Mesh::Draw(OpenGLShader& shader)
    {
        // unsigned int diffuseNr = 1;
        // unsigned int specularNr = 1;
        // // unsigned int normalNr = 1;
        // // unsigned int heightNr = 1;
        // for (unsigned int i = 0; i < textures.size(); i++)
        // {
        //     auto 
        //     std::string number;
        //     std::string name = textures[i].type;
        //     if (name == "texture_diffuse")
        //         number = std::to_string(diffuseNr++);
        //     else if (name == "texture_specular")
        //         number = std::to_string(specularNr++);
        //     else if (name == "texture_normal")
        //         number = std::to_string(normalNr++);
        //     else if (name == "texture_height")
        //         number = std::to_string(heightNr++);
        //     shader.SetUniform1i((name + number).c_str(), i);
        // }

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++);

            // shader.setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);

        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::setupMesh()
    {
        // Phoenix::BufferLayout layout = {
        //     { ShaderDataType::Float3, "aPos" },
        //     { ShaderDataType::Float3, "aNormal" },
        //     { ShaderDataType::Float2, "aTexCoords" },
        //     // { ShaderDataType::Float3, "aTangent" },
        //     // { ShaderDataType::Float3, "aBitangent"}
        // };
        // Ref<VertexArray> vertexArray = Application::Get().GetRenderer()->s_RendererAPI->CreateVertexArray();
        // Ref<VertexBuffer> vertexBuffer = Application::Get().GetRenderer()->s_RendererAPI->CreateVertexBuffer((void*)vertices.data(), vertices.size() * sizeof(Vertex));
        // Ref<IndexBuffer> indexBuffer = Application::Get().GetRenderer()->s_RendererAPI->CreateIndexBuffer(indices);
        // vertexBuffer->SetLayout(layout);
        // vertexArray->AddVertexBuffer(vertexBuffer);
        // vertexArray->SetIndexBuffer(indexBuffer);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
  
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                     &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
}
