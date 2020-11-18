#pragma once

#include "neon_pch.h"

#include <glad/glad.h>

namespace Neon {
    class Shader {
    public:
        Shader(const std::string &vertexStr, const std::string &fragmentStr);
        ~Shader();
        
        void Bind() const;
        void UnBind() const;
        
    private:
        void HandleCompileError(GLuint shader);
    private:
        uint32_t _rendererId;
    };
}
