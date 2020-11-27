#pragma once

#include "Neon/Renderer/RendererAPI.h"
#include "Neon/Renderer/VertexArray.h"

namespace Neon {

    class RenderCommand {
    public:
        inline static void SetClearColor(const glm::vec4& color) {
            m_RendererApi->SetClearColor(color);
        }
        inline static void Clear() {
            m_RendererApi->Clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray> vertexArray) {
            m_RendererApi->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI* m_RendererApi;
    };
}  // namespace Neon
