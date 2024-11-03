#pragma once
#include <string>

#include "Mesh.h"
#include "Core/Graphics/OpenGLImpl/include/OpenGLShader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace Phoenix
{
    class Model
    {
    public:
        Model(std::string& path)
        {
            LoadModel(path);
            directory = path.substr(0, path.find_last_of('/'));
        }

        void Draw(OpenGLShader& shader);
    private:
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<MeshTexture> textures_loaded; 
        void LoadModel(std::string& path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    };
}
