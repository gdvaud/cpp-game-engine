#include "Buffer.h"

#include "Neon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Neon {
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, count);
            case RendererAPI::API::None: NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
            default: NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        }
        return nullptr;
    }
    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
            case RendererAPI::API::None: NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
            default: NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        }
        return nullptr;
    }
}  // namespace Neon
