#include "OpenGLShader.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace Neon {
    static GLenum ShaderTypeFromString(const std::string& type) {
        if (type == "vertex") return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

        NEO_CORE_ASSERT(false, "Unknown shader type");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath) {
        // Fetch sources
        std::string sources;
        {
            std::ifstream in(filepath, std::ios::in, std::ios::binary);
            if (in) {
                in.seekg(0, std::ios::end);
                sources.resize(in.tellg());
                in.seekg(0, std::ios::beg);
                in.read(&sources[0], sources.size());
                in.close();
            } else {
                NEO_CORE_ERROR("Could not open file {0}", filepath);
            }
        }

        // Parse sources
        std::unordered_map<GLenum, std::string> shaderSources;
        {
            const char* typeToken = "#type ";
            const auto typeTokenLength = strlen(typeToken);
            auto typeTokenPos = sources.find(typeToken);
            while (typeTokenPos != std::string::npos) {
                auto eol = sources.find_first_of("\r\n", typeTokenPos);
                NEO_CORE_ASSERT(eol != std::string::npos, "Shader syntax error");

                auto begin = typeTokenPos + typeTokenLength;
                auto typeStr = sources.substr(begin, eol - begin);
                auto type = ShaderTypeFromString(typeStr);
                NEO_CORE_ASSERT(type, "Invalid shader type specified");

                auto nextLinePos = sources.find_first_not_of("\r\n", eol);
                typeTokenPos = sources.find(typeToken, nextLinePos);
                shaderSources[type] = sources.substr(
                    nextLinePos,
                    typeTokenPos - (nextLinePos == std::string::npos ? sources.size() - 1 : nextLinePos));
            }
        }

        std::vector<GLuint> shaderIDs(shaderSources.size());
        for (auto& kv : shaderSources) {
            shaderIDs.push_back(CompileShader(kv.first, kv.second));
        }

        LinkShaders(shaderIDs);
    }
    OpenGLShader::OpenGLShader(const std::string& vertexStr, const std::string& fragmentStr) {
        std::unordered_map<GLenum, std::string> shaderSources;
        shaderSources[GL_VERTEX_SHADER] = vertexStr;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentStr;

        std::vector<GLuint> shaderIDs(shaderSources.size());
        for (auto& kv : shaderSources) {
            shaderIDs.push_back(CompileShader(kv.first, kv.second));
        }

        LinkShaders(shaderIDs);
    }

    GLuint OpenGLShader::CompileShader(GLenum type, const std::string& source) {
        GLuint shader = glCreateShader(type);

        const GLchar* sourceChar = source.c_str();
        glShaderSource(shader, 1, &sourceChar, nullptr);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            NEO_CORE_CRITICAL("{0}", infoLog.data());

            glDeleteShader(shader);
            NEO_CORE_ASSERT(false, "Shader compilation failure");
        }

        return shader;
    }
    void OpenGLShader::LinkShaders(const std::vector<GLuint>& shaderIDs) {
        m_RendererId = glCreateProgram();

        for (auto shaderId : shaderIDs) {
            glAttachShader(m_RendererId, shaderId);
        }

        glLinkProgram(m_RendererId);

        GLint isLinked = 0;
        glGetProgramiv(m_RendererId, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_RendererId);
            for (auto shaderId : shaderIDs) {
                glDeleteShader(shaderId);
            }

            NEO_CORE_CRITICAL("Shader linking error: {0}", infoLog.data());
            NEO_CORE_ASSERT(false, "Shader linking failure");
        }

        for (auto shaderId : shaderIDs) {
            glDetachShader(m_RendererId, shaderId);
        }
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererId);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererId);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform1i(location, value);
    }
}  // namespace Neon
