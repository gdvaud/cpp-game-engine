#include "Shader.h"

#include "Neon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Neon {
    Ref<Shader> Shader::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(path);
            case RendererAPI::API::None: NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
        }
        NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& vertexStr, const std::string& fragmentStr) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(vertexStr, fragmentStr);
            case RendererAPI::API::None: NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
        }
        NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}  // namespace Neon
