#pragma once

#include "Neon/Renderer/RendererAPI.h"

namespace Neon {
    class OpenGLRendererAPI : public RendererAPI {
    public:
        void Init() override;
        void Shutdown() override;

        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}  // namespace Neon
