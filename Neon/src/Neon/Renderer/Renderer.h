#pragma once

#include "Neon/Renderer/RendererAPI.h"
#include "Neon/Renderer/VertexArray.h"

namespace Neon {
    class Renderer {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const Ref<VertexArray> vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}  // namespace Neon
