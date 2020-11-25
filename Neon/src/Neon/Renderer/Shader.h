#pragma once

#include "neon_pch.h"

namespace Neon {
    class Shader {
    public:
        Shader(const std::string& vertexStr, const std::string& fragmentStr);
        ~Shader();

        void Bind() const;
        void UnBind() const;

    private:
        void HandleCompileError(uint32_t shader);

    private:
        uint32_t _rendererId;
    };
}  // namespace Neon
