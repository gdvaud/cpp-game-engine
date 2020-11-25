#include "Renderer.h"

#include "Neon/Renderer/RenderCommand.h"

namespace Neon {
    void Renderer::BeginScene() {}
    void Renderer::EndScene() {}

    void Renderer::Submit(const Ref<VertexArray> vertexArray) {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}  // namespace Neon
