// RenderCommand.h

#pragma once
#include <cstdint>

#include "RendererAPI.h"
#include "../../../Core/Base/Base.h"
#include "../../DataObjects/include/VertexArray.h"
#include "../../../Core/Maths/include/Maths.h"

namespace Phoenix
{
    class PHOENIX_API RenderCommand
    {
    public:
        static void Init()
        {
            s_RendererAPI->Init();
        }

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_RendererAPI->SetViewport(x, y, width, height);
        }

        static void SetClearColor(const Maths::Color color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        static void Clear()
        {
            s_RendererAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
        {
            s_RendererAPI->DrawIndexed(vertexArray, indexCount);
        }

        static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
        {
            s_RendererAPI->DrawLines(vertexArray, vertexCount);
        }

    private:
        static Scope<RendererAPI> s_RendererAPI;
    };
}