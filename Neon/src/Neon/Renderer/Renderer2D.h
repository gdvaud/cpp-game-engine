#pragma once

#include <glm/glm.hpp>

#include "Neon/Renderer/OrthographicCamera.h"
#include "Neon/Graphic/Shader.h"
#include "Neon/Graphic/VertexArray.h"

namespace Neon {
    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Ref<OrthographicCamera>& camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

    private:
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);

    private:
        struct Renderer2DData {
            Ref<VertexArray> QuadVertexArray;
            Ref<Shader> FlatColorShader;
        };

    private:
        static Renderer2DData s_Data;
    };
}  // namespace Neon
