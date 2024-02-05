// OpenGLRendererAPI.h

#pragma once
#include "RendererAPI.h"


namespace Phoenix
{
    class OpenGLRendererAPI: public RendererAPI
    {
    public:
        void Init() override;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

        void SetClearColor(const Maths::Color color) override;

        void Clear() override;

        void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
        void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) override;

        void SetLineWidth(float width) override;

        
        virtual Ref<VertexArray> CreateVertexArray() override;
        virtual Ref<VertexBuffer> CreateVertexBuffer(std::vector<float> vertices) override;
        virtual Ref<IndexBuffer> CreateIndexBuffer(std::vector<uint32_t> indices) override;
        virtual Ref<Shader> CreateShader(std::string name, const char* vertexShader, const char* fragmentShader) override;
    };
}
