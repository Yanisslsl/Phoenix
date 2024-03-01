// RendererAPI.h

#pragma once
#include <cstdint>
#include <string>

#include "../../../Core/Base/Base.h"
#include "../../DataObjects/include/VertexArray.h"
#include "../../../Core/Maths/include/Maths.h"
#include "Common/Core/Graphics/DataObjects/include/Texture.h"

namespace Phoenix
{
    class Shader;

    class PHOENIX_API RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1
            // Add more as we go along
            // PSP = 2
        };



        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        // @TODO: add GLM support
        // virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void SetClearColor(const Maths::Color color) = 0;

        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
        virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

        virtual void SetLineWidth(float width) = 0;

        virtual Ref<VertexArray> CreateVertexArray() = 0;
        virtual Ref<VertexBuffer> CreateVertexBuffer(std::vector<float> vertices) = 0;
        virtual Ref<IndexBuffer> CreateIndexBuffer(std::vector<uint32_t> indices) = 0;
        virtual Ref<Shader> CreateShader(std::string name, const char* vertexShader, const char* fragmentShader) = 0;
        virtual Ref<Shader> CreateShader(std::string name) = 0;
        virtual Ref<Texture2D> CreateTexture2D(std::string texturePath) = 0;
        static API GetAPI() { return s_API; }
        static Scope<RendererAPI> Create();
    private:
        static API s_API;
        static Scope<RendererAPI> s_RendererAPI;
    };
}
