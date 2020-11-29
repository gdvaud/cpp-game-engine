#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Neon/Core/Base.h"

namespace Neon {
    class Shader {
    public:
        static Ref<Shader> Create(const std::string& vertexStr, const std::string& fragmentStr);

        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
        virtual void UploadUniformInt(const std::string& name, int value) = 0;
    };
}  // namespace Neon
