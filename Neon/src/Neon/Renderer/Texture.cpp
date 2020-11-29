#include "Texture.h"

#include "Neon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Neon {

    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
            case RendererAPI::API::None:
                NEO_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
                return nullptr;
        }
        NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}  // namespace Neon