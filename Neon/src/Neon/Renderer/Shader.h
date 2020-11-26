#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Neon {
    class Shader {
    public:
        Shader(const std::string& vertexStr, const std::string& fragmentStr);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        void HandleCompileError(uint32_t shader);

    private:
        uint32_t _rendererId;
    };
}  // namespace Neon
