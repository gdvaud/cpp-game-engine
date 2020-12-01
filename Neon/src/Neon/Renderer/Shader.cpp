#include "Shader.h"

#include "Neon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Neon {
    Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, filepath);
            case RendererAPI::API::None: NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
        }
        NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexStr, const std::string& fragmentStr) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexStr, fragmentStr);
            case RendererAPI::API::None: NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
        }
        NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, Ref<Shader>& shader) {
        m_Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
        auto shader = Shader::Create(name, filepath);
        m_Shaders[name] = shader;
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexStr, const std::string& fragmentStr) {
        auto shader = Shader::Create(name, vertexStr, fragmentStr);
        m_Shaders[name] = shader;
        return shader;
    }

    Ref<Shader>& ShaderLibrary::Get(const std::string& name) {
        NEO_CORE_ASSERT(Exists(name), "Shader not found in library")
        return m_Shaders[name];
    }
    bool ShaderLibrary::Exists(const std::string& name) {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}  // namespace Neon
