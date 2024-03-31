// RendererAPI.h

#pragma once
#include <cstdint>
#include <string>

#include "Core/Graphics/DataObjects/include/Texture.h"
#include "Core/Graphics/DataObjects/include/VertexArray.h"
#include "Utils/Color.h"


namespace Phoenix
{
    class Shader;
    class PHOENIX_API RendererAPI
    {
    public:
        /**
         * \brief The API that the Renderer is using
         */
        enum class API
        {
            None = 0,
            OpenGL = 1
            // Add more as we go along
            // PSP = 2
        };

        /** 
         * \brief Destructor
         */
        virtual ~RendererAPI() = default;

        /** 
         * \brief Initialization of the Renderer
         */
        virtual void Init() = 0;

        /** 
         * \brief Set the viewport of the window
         * \param x 
         * \param y 
         * \param width 
         * \param height 
         */
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        /** 
         * \brief Set the clear color of the window
         * \param color 
         */
        virtual void SetClearColor(const ColorRGBA color) = 0;

        /** 
         * \brief Clear the window
         */
        virtual void Clear() = 0;


        /** 
         * \brief Draw the indexed vertex array
         * \param vertexArray 
         * \param indexCount 
         */
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

        /** 
         * \brief Draw the lines of the vertex array
         * \param vertexArray 
         * \param vertexCount 
         */
        virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;


        /** 
         * \brief Set the line width
         * \param width 
         */
        virtual void SetLineWidth(float width) = 0;

         /** 
         * \brief Create a VertexArray
         * \return Ref of VertexArray
         */
        virtual Ref<VertexArray> CreateVertexArray() = 0;

         /** 
         * \brief Create a VertexBuffer
         * \param vertices 
         * \return Ref of VertexBuffer
         */
        virtual Ref<VertexBuffer> CreateVertexBuffer(std::vector<float> vertices) = 0;

        /** 
         * \brief Create a IndexBuffer
         * \param indices 
         * \return Ref of IndexBuffer
         */
        virtual Ref<IndexBuffer> CreateIndexBuffer(std::vector<uint32_t> indices) = 0;

         /** 
         * \brief Create a Shader
         * \param name 
         * \param vertexShader 
         * \param fragmentShader 
         * \return Ref of Shader
         */
        virtual Ref<Shader> CreateShader(std::string name, const char* vertexShader, const char* fragmentShader) = 0;

        /** 
         * \brief Create a Shader
         * \param name 
         * \return Ref of Shader
         */
        virtual Ref<Shader> CreateShader(std::string name) = 0;

        /** 
         * \brief Create a Texture2D
         * \param texturePath 
         * \return Ref of Texture2D
         */
        virtual Ref<Texture2D> CreateTexture2D(std::string texturePath) = 0;

        /** 
         * \brief Create a Texture2D
         * \param texturePath 
         * \return Ref of Texture2D
         */
        static API GetAPI() { return s_API; }

        /** 
         * \brief Create correct RendererAPI based on the API
         */
        static Scope<RendererAPI> Create();
    private:
        static API s_API;
        static Scope<RendererAPI> s_RendererAPI;
    };
}
