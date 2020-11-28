#include "Renderer.h"

#include "Neon/Renderer/RenderCommand.h"

namespace Neon {

    Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::BeginScene(const Ref<OrthographicCamera>& camera) {
        m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
    }
    void Renderer::EndScene() {}

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}  // namespace Neon
