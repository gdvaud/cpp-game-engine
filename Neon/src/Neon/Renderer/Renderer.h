#pragma once

#include "Neon/Renderer/OrthographicCamera.h"
#include "Neon/Renderer/RendererAPI.h"
#include "Neon/Renderer/Shader.h"
#include "Neon/Renderer/VertexArray.h"

namespace Neon {
    class Renderer {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

    private:
        static SceneData* _sceneData;
    };
}  // namespace Neon
