#include "Renderer.h"

#include "Neon/Renderer/RenderCommand.h"

namespace Neon {

    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init() { RenderCommand::Init(); }
    void Renderer::Shutdown() { RenderCommand::Shutdown(); }

    void Renderer::OnWindowResized(uint32_t width, uint32_t height) { RenderCommand::SetViewport(0, 0, width, height); }

    void Renderer::BeginScene(const Ref<OrthographicCamera>& camera) {
        s_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
    }
    void Renderer::EndScene() {}

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}  // namespace Neon
