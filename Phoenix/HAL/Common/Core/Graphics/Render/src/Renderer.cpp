#include "../include/Renderer.h"

namespace Phoenix {
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init() {
        RenderCommand::Init();
        //@TODO add Renderer 3D
        // Renderer3D::Init();
    }

    void Renderer::Shutdown() {
        //@TODO add Renderer 3D
        // Renderer3D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    // void Renderer::BeginScene(OrthographicCamera& camera) {
    //     s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    // }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Maths::Matrix4& transform) {
        shader->Bind();
        // shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        // shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}