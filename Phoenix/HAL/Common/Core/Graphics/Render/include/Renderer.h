// Renderer.h

#pragma once
#include <memory>

#include <map>
#include "RendererAPI.h"
#include "../../DataObjects/include/Shader.h"
#include "../../../Core/Maths/include/Maths.h"
#include "../../../Core/Base/Base.h"


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
    };
    class PHOENIX_API Renderer
    {
    public:
        static void Init()
        {
            s_RendererAPI->Init();
        }
        static void OnWindowResize(uint32_t width, uint32_t height)
        {
            s_RendererAPI->SetViewport(0, 0, width, height);
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
        static void Shutdown();
        
        static void BeginScene();
        static void EndScene();
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Maths::Matrix4& transform = {});
        
        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        static void Renderer::CreateShape(std::string name, std::vector<float> vertices, std::vector<uint32_t> indices, const char* vertexShader, const char* fragmentShader, const BufferLayout bufferlayout ,const Maths::Matrix4& transform = {});
        static Ref<Shader> Renderer::GetShader(std::string name);
        static void OnUpdate();
    private:
        struct SceneData
        {
            Maths::Matrix4 ViewProjectionMatrix;
        };
        static Scope<SceneData> s_SceneData;
        static std::map<std::string, Ref<VertexArray>> s_VertexArrays;
        static std::map<std::string, ShapeData> s_ShapeData;
        static Scope<RendererAPI> s_RendererAPI;
        static Ref<VertexArray> m_Vertex_Array;
        static Ref<Shader> m_Shader;
    };
}
