#pragma once

#include "Neon/Renderer/OrthographicCamera.h"
#include "Neon/Renderer/RendererAPI.h"
#include "Neon/Renderer/Shader.h"
#include "Neon/Renderer/VertexArray.h"

namespace Neon {
    class Renderer {
    public:
        static void Init();
        static void Shutdown();

        static void OnWindowResized(uint32_t width, uint32_t height);

        static void BeginScene(const Ref<OrthographicCamera>& camera);
        static void EndScene();

        static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader,
                           const glm::mat4& transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

    private:
        static Scope<SceneData> s_SceneData;
    };
}  // namespace Neon
