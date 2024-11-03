#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Core.h"
#include "Core/Graphics/DataObjects/include/VertexArray.h"
#include "Core/Graphics/OpenGLImpl/include/OpenGLShader.h"

namespace Phoenix
{
    inline int MAX_BONE_INFLUENCE = 4;

    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // // tangent
        // glm::vec3 Tangent;
        // // bitangent
        // glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        // int m_BoneIDs[MAX_BONE_INFLUENCE];
        // //weights from each bone
        // float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct MeshTexture {
        unsigned int id;
        std::string type;
        std::string path;
    };
    
    class PHOENIX_API Mesh
    {
    public:
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshTexture>      textures;

        Mesh(std::vector <Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures): vertices(vertices), indices(indices), textures(textures)
        {
            setupMesh();
        }

        void Draw(OpenGLShader& shader);
    private:
        void setupMesh();
        Ref<VertexArray> vertexArray;
        Ref<VertexBuffer> vertexBuffer;
        Ref<IndexBuffer> indexBuffer;
        unsigned int VAO, VBO, EBO;
    };
}
