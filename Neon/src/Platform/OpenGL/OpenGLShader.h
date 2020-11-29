#pragma once

#include "Neon/Renderer/Shader.h"

namespace Neon {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexStr, const std::string& fragmentStr);
        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
        void UploadUniformInt(const std::string& name, int value) override;

    private:
        void HandleCompileError(uint32_t shader);

    private:
        uint32_t m_RendererId;
    };
}  // namespace Neon
