#pragma once

#include "Neon/Renderer/Shader.h"

namespace Neon {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& name, const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string& vertexStr, const std::string& fragmentStr);
        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
        void UploadUniformInt(const std::string& name, int value) override;

        const std::string& GetName() const override;

    private:
        GLuint CompileShader(GLenum type, const std::string& source);
        void LinkShaders(const std::vector<GLuint>& shaderIDs);

    private:
        uint32_t m_RendererId;
        std::string m_Name;
    };
}  // namespace Neon
