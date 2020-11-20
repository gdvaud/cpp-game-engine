#include "Shader.h"

#include "Core.h"

namespace Neon {
    Shader::Shader(const std::string &vertexStr, const std::string &fragmentStr) {
        // ===== VERTEX =====
        // Create an empty shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        
        // Send the vertex shader to GL
        const GLchar *vertexSource = vertexStr.c_str();
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        
        glCompileShader(vertexShader);
        
        GLint vertexShaderCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled);
        if (vertexShaderCompiled == GL_FALSE) {
            HandleCompileError(vertexShader);
            glDeleteShader(vertexShader);
            NEO_CORE_ASSERT(false, "Vertex shader compilation failure");
            return;
        }
    
        // ===== FRAGMENT =====
        // Create an empty shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
        // Send the vertex shader to GL
        const GLchar *fragmentSource = fragmentStr.c_str();
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    
        glCompileShader(fragmentShader);
    
        GLint fragmentShaderCompiled = 0;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);
        if (fragmentShaderCompiled == GL_FALSE) {
            HandleCompileError(fragmentShader);
            
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            
            NEO_CORE_ASSERT(false, "Fragment shader compilation failure");
            return;
        }
        
        // ===== LINKING =====
        _rendererId = glCreateProgram();
        GLuint program = _rendererId;
        
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        
        glLinkProgram(program);
        
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_LINK_STATUS, &maxLength);
            
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            
            glDeleteProgram(program);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            
            NEO_CORE_CRITICAL("{0}", infoLog.data());
            NEO_CORE_ASSERT(false, "Shader linking failure");
            return;
        }
        
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }
    
    void Shader::HandleCompileError(uint32_t shader) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
        
        NEO_CORE_CRITICAL("{0}", infoLog.data());
    }
    
    Shader::~Shader() {
        glDeleteProgram(_rendererId);
    }
    
    void Shader::Bind() const {
        glUseProgram(_rendererId);
    }
    
    void Shader::UnBind() const {
        glUseProgram(0);
    }
}