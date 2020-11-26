#include "Renderer.h"

#include "Neon/Renderer/RenderCommand.h"

namespace Neon {

    Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera) {
        _sceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }
    void Renderer::EndScene() {}

    void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", _sceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}  // namespace Neon
