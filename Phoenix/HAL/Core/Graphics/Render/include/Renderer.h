// Renderer.h

#pragma once
#include <memory>
#include <map>
#include "RendererAPI.h"
#include "Core/Scene/include/Camera.h"
#include "Utils/Color.h"


namespace Phoenix
{

    /** 
     * \brief TextureData struct
     *        Used to store the texture data
     */
    struct TextureData
    {
       std::vector<Ref<Texture2D>> textures;
       bool isEnable;
       int currentTextureIndex;
    };

    /** 
     * \brief ShapeData struct
     *        Used to store the shape data
     */
    struct ShapeData
    {
       ShapeData(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer, Ref<VertexArray> vertexArray, Ref<Shader> shader, BufferLayout bufferlayout, glm::mat4 modelMat)
           : vertexBuffer(vertexBuffer), indexBuffer(indexBuffer), vertexArray(vertexArray), shader(shader), bufferlayout(bufferlayout), modelMat(modelMat)
       {
         texturesDatas = std::map<std::string, TextureData>();
          currentTextureData = TextureData();
       }
        void EnableTextureData(std::string name)
        {
           for(auto& textureData : texturesDatas)
           {
               if(textureData.first == name)
               {
                 textureData.second.isEnable = true;
                 currentTextureData = textureData.second;
               }
               textureData.second.isEnable = false;
               textureData.second.currentTextureIndex = 0;
           }
        }
        Ref<VertexBuffer> vertexBuffer;
        Ref<IndexBuffer> indexBuffer;
        Ref<VertexArray> vertexArray;
        Ref<Shader> shader;
        BufferLayout bufferlayout;
        glm::mat4 modelMat;
        Ref<Texture2D> texture;
        //  === Animation ===
        std::map<std::string, TextureData> texturesDatas;
        TextureData currentTextureData;
        //  === Animation ===
        ColorType color;
    };


    /**
     * \brief @REFACTORED Renderer class need to be refactored to be inherited from Renderer2D and Renderer3D
     * Move all no 2D related functions to Renderer2D and all 3D related functions to Renderer3D, will be ok for now
     */
    class PHOENIX_API Renderer
    {
    public:

        Renderer();

        ~Renderer();
        
        /**
         * \brief Initialization of the Renderer call this function in the Application constructor
         */
        void Init();

        /**
         * \brief EventListener for window resize
         * \param width
         * \param height
         */
        void OnWindowResize(uint32_t width, uint32_t height);
        
        /**
         * \brief Set the clear color of the window
         * \param color
         */
        void SetClearColor(const ColorRGBA color);
        
        /**
         * \brief Clear the window
         */
        void Clear();
        
        /**
         * \brief Draw the indexed vertex array
         * \param vertexArray
         * \param indexCount
         */
        void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);
        
        /**
         * \brief Draw the lines
         * \param vertexArray
         * \param vertexCount
         */
        void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount);

        /**
         * \brief Shutdown the Renderer
         */
        void Shutdown();
        /** 
         * \brief Begin the scene
         */
        void BeginScene();

        /** 
         * \brief End the scene
         */
        void EndScene();

        /**
         * \brief Submit the shape to the renderer
         * \param shader 
         * \param vertexArray
         * \param texture
         * \param color
         * \param modelMat
         * \param textureData
         */
        void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, Ref<Texture> texture, ColorType color, glm::mat4 modelMat, TextureData textureData);

        /**
         * \brief Create quad only for 2D
         */
         void CreateQuad(std::string name, const char* texturePath, const glm::mat4 modelMat);

         void CreateQuad(std::string name, const ColorType color , const glm::mat4 modelMat);

        /**
         * \brief Create 2D shape
         * \param name 
         * \param vertices 
         * \param indices 
         * \param vertexShader 
         * \param fragmentShader 
         * \param bufferlayout 
         * \param transform 
         */
        void CreateShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const glm::mat4 modelMat);

        /**
         * \brief Create textured 2D shape
         * \param name 
         * \param vertices 
         * \param indices 
         * \param vertexShader 
         * \param fragmentShader 
         * \param bufferlayout 
         * \param texturePath 
         * \param transform 
         */
        void CreateTexturedShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const char* texturePath, const glm::mat4 modelMat);

        
        /** 
         * \brief Set textures paths for specific shape
         * \param shapeName
         * \param name 
         * \param texturesPaths 
         */
        void SetTexturesPaths(std::string shapeName, std::string name, std::vector<std::string> texturesPaths);

        void CreateCube(std::string name, const char* texturePath, const glm::mat4 modelMat);

        void CreateCube(std::string name, ColorType color, const glm::mat4 modelMat);


        /** 
         * \brief Set texture index
         * \param shapeName
         * \param textureIndex 
         */
        void SetTextureIndex(std::string shapeName, int textureIndex);

        /** 
         * \brief Enable shape texture
         *        Used for enabling the texture of the shape
         * \param shapeName
         * \param name 
         */
        void EnableShapeTexture(std::string shapeName, std::string name);

        /** 
         * \brief Disable shape texture
         * \param name 
         */
        void DeleteShape(std::string name);
        /**
         * \brief 
         * \return The rendered API, be cautious when using RendererAPI::API
         */
        RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        /**
         * \brief Return the shader by name, useful for updating the shader
         * \param name 
         * \return 
         */
        Ref<Shader> GetShader(std::string name);

        /**
         * \brief Update the Renderer
         *
         * This function is responsible for rendering all of the objects in the scene
         */
        void OnUpdate();

     
        /**
         * \brief Begin the scene
         * \param camera 
         */
        void BeginScene(Camera& camera);

        /**
         * \brief Update the shape model matrix
         * \param name 
         * \param modelMat 
         */
        void UpdateModelMatrix(std::string name, glm::mat4 modelMat);


    protected:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };
        Scope<SceneData> s_SceneData;
     
        /**
         * \brief Internal renderer data for shapes, used to keep track of the shapes and their data
         */
        std::map<std::string, ShapeData> s_ShapeData;

        /**
         * \brief Abstraction of the Graphics API 
         */
        Scope<RendererAPI> s_RendererAPI;
    };
}
