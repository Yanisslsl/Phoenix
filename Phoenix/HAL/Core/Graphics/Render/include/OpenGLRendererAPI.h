// OpenGLRendererAPI.h

#pragma once
#include "RendererAPI.h"
#include "Utils/Color.h"


namespace Phoenix
{

    /**
     * \brief OpenGL Renderer API implementation
     */
    class OpenGLRendererAPI: public RendererAPI
    {
    public:
        /**
         * \brief Initialization of the Renderer
         */
        void Init() override;

        /**
         * \brief Set the viewport of the window
         * \param x 
         * \param y 
         * \param width 
         * \param height 
         */
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        /**
         * \brief Set the clear color of the window
         * \param color 
         */
        void SetClearColor(const ColorRGBA color) override;

        /**
         * \brief Clear the window
         */
        void Clear() override;

        /**
         * \brief Draw the indexed vertex array
         * \param vertexArray 
         * \param indexCount 
         */
        void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;

        /**
         * \brief Draw the lines of the vertex array
         * \param vertexArray 
         * \param vertexCount 
         */
        void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) override;

        /**
         * \brief Set the line width
         * \param width 
         */
        void SetLineWidth(float width) override;


        /**
         * \brief Create a VertexArray
         * \return 
         */
        virtual Ref<VertexArray> CreateVertexArray() override;

        /**
         * \brief Create a VertexBuffer
         * \param vertices 
         * \return 
         */
        virtual Ref<VertexBuffer> CreateVertexBuffer(std::vector<float> vertices) override;

        /**
         * \brief Create an IndexBuffer
         * \param indices 
         * \return 
         */
        virtual Ref<IndexBuffer> CreateIndexBuffer(std::vector<uint32_t> indices) override;

        /**
         * \brief Create a Shader
         * \param name 
         * \param vertexShader 
         * \param fragmentShader 
         * \return 
         */
        virtual Ref<Shader> CreateShader(std::string name, const char* vertexShader, const char* fragmentShader) override;

        /**
         * \brief Create a Shader
         * \param name 
         * \return 
         */
        virtual Ref<Shader> CreateShader(std::string name) override;
     
        /**
         * \brief Create a Texture2D
         * \param texturePath 
         * \return 
         */
        virtual Ref<Texture2D> CreateTexture2D(std::string texturePath) override;
    };
}
