// Renderer.h

#pragma once
#include <memory>

#include "RenderCommand.h"
#include "RendererAPI.h"
#include "../../DataObjects/include/Shader.h"
#include "../../../Core/Maths/include/Maths.h"
#include "../../../Core/Base/Base.h"


namespace Phoenix
{
    class PHOENIX_API Renderer
    {
    public:
        static void Init();
        static void Shutdown();
        
        static void OnWindowResize(uint32_t width, uint32_t height);
        
        // static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Maths::Matrix4& transform = {});
        
        // static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Maths::Matrix4& transform = glm::mat4(1.0f));

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            Maths::Matrix4 ViewProjectionMatrix;
        };
        static Scope<SceneData> s_SceneData;
    };
}
