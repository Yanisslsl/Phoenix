// RendererAPI.h

#pragma once
#include <cstdint>
#include <string>

#include "../../../Core/Base/Base.h"



namespace Phoenix
{
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1
            // Add more as we go along
            // PSP = 2
        };

        // @TODO: delete when glm is added
        struct Matrix4 {
            float m[4][4];
        };
         
        struct Vec4
        {
            float x, y, z, w;
        };
        struct Vec3
        {
            float x, y, z;
        };
        struct Vec2
        {
            float x, y;
        };

        struct Color
        {
            float r, g, b, a;
        };

        virtual ~RendererAPI() = default;

        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        // @TODO: add GLM support
        // virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void SetClearColor(const Color color) = 0;

        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
        virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

        virtual void SetLineWidth(float width) = 0;

        static API GetAPI() { return s_API; }
        static Scope<RendererAPI> Create();
    private:
        static API s_API;
        
    };
}
