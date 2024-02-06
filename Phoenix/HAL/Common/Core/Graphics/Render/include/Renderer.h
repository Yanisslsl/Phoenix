// Renderer.h

#pragma once
#include <memory>

#include <map>
#include "RendererAPI.h"
#include "../../DataObjects/include/Shader.h"
#include "../../../Core/Maths/include/Maths.h"
#include "../../../Core/Base/Base.h"
#include "Common/Core/Graphics/DataObjects/include/Texture.h"
#include "Common/Core/Scene/include/OrthographicCamera.h"


namespace Phoenix
{

    struct ShapeData
    {
        Ref<VertexBuffer> vertexBuffer;
        Ref<IndexBuffer> indexBuffer;
        Ref<VertexArray> vertexArray;
        Ref<Shader> shader;
        BufferLayout bufferlayout;
        Maths::Matrix4 transform;
        Ref<Texture2D> texture;
    };
    class PHOENIX_API Renderer
    {
    public:
        
        /**
         * \brief Initialization of the Renderer call this function in the Application constructor
         */
        static void Init();

        /**
         * \brief EventListener for window resize
         * \param width
         * \param height
         */
        static void OnWindowResize(uint32_t width, uint32_t height);
        
        /**
         * \brief Set the clear color of the window
         * \param color
         */
        static void SetClearColor(const Maths::Color color);
        
        /**
         * \brief Clear the window
         */
        static void Clear();
        
        /**
         * \brief Draw the indexed vertex array
         * \param vertexArray
         * \param indexCount
         */
        static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);
        
        /**
         * \brief Draw the lines
         * \param vertexArray
         * \param vertexCount
         */
        static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount);

        /**
         * \brief Shutdown the Renderer
         */
        static void Shutdown();
        
        static void BeginScene();
        static void EndScene();

        /**
         * \brief  Bind the shader and vertex array and draw the indexed vertex array
         * \param shader 
         * \param vertexArray
         * \param texture
         * \param transform 
         */
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, Ref<Texture> texture, const Maths::Matrix4& transform = {});

        /**
         * \brief Create shape
         * \param name 
         * \param vertices 
         * \param indices 
         * \param vertexShader 
         * \param fragmentShader 
         * \param bufferlayout 
         * \param transform 
         */
        static void Renderer::CreateShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const Maths::Matrix4& transform = {});

        /**
         * \brief Create textured shape
         * \param name 
         * \param vertices 
         * \param indices 
         * \param vertexShader 
         * \param fragmentShader 
         * \param bufferlayout 
         * \param texturePath 
         * \param transform 
         */
        static void Renderer::CreateTexturedShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const char* texturePath, const Maths::Matrix4& transform = {});

        /**
         * \brief 
         * \return The rendered API, be cautious when using RendererAPI::API
         */
        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        /**
         * \brief Return the shader by name, useful for updating the shader
         * \param name 
         * \return 
         */
        static Ref<Shader> Renderer::GetShader(std::string name);

        /**
         * \brief Update the Renderer
         *
         * This function is responsible for rendering all of the objects in the scene
         */
        static void OnUpdate();

     
        /**
         * \brief Begin the scene
         * \param camera 
         */
        static void BeginScene(OrthographicCamera& camera);
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };
        static Scope<SceneData> s_SceneData;
     
        /**
         * \brief Internal renderer data for shapes, used to keep track of the shapes and their data
         */
        static std::map<std::string, ShapeData> s_ShapeData;

        /**
         * \brief Abstraction of the Graphics API 
         */
        static Scope<RendererAPI> s_RendererAPI;
    };
}
