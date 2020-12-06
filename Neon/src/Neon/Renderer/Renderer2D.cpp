#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Neon/Renderer/RenderCommand.h"

namespace Neon {

    Renderer2D::Renderer2DData Renderer2D::s_Data;

    void Renderer2D::Init() {
        s_Data.QuadVertexArray = VertexArray::Create();

        // clang-format off
        float quadVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        // clang-format on
        uint32_t quadIndices[6] = {0, 1, 2, 2, 3, 0};

        Ref<VertexBuffer> quadVB = VertexBuffer::Create(quadVertices, sizeof(quadVertices) / sizeof(float));
        quadVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
        s_Data.QuadVertexArray->AddVertexBuffer(quadVB);

        Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
        s_Data.QuadVertexArray->SetIndexBuffer(quadIB);

        s_Data.FlatColorShader = Shader::Create("FlatColor", "Neon/assets/shaders/FlatColor.glsl");
    }
    void Renderer2D::Shutdown() {
        s_Data.QuadVertexArray.reset();
        s_Data.FlatColorShader.reset();
    }

    void Renderer2D::BeginScene(const Ref<OrthographicCamera>& camera) {
        s_Data.FlatColorShader->Bind();
        s_Data.FlatColorShader->SetMat4("u_ViewProjection", camera->GetViewProjectionMatrix());
    }
    void Renderer2D::EndScene() {}

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
        DrawQuad(glm::vec3(position.x, position.y, 0), size, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
        auto transform =
            glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1));
        DrawQuad(transform, color);
    }

    void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color) {
        s_Data.FlatColorShader->Bind();
        s_Data.FlatColorShader->SetMat4("u_Transform", transform);
        s_Data.FlatColorShader->SetFloat4("u_Color", color);

        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
    }
}  // namespace Neon