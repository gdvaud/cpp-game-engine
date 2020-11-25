#pragma once

#include "Neon/Renderer/RendererAPI.h"
#include "Neon/Renderer/VertexArray.h"

namespace Neon {

    class RenderCommand {
    public:
        inline static void SetClearColor(const glm::vec4& color) {
            _rendererAPI->SetClearColor(color);
        }
        inline static void Clear() {
            _rendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray> vertexArray) {
            _rendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI* _rendererAPI;
    };
}  // namespace Neon
