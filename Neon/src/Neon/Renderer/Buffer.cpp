#include "Buffer.h"

#include "Renderer.h"
#include "Core.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Neon {
    VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, count);
            case RendererAPI::None:
                NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
            default:
                NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        }
        return nullptr;
    }
    IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, count);
            case RendererAPI::None:
                NEO_CORE_ASSERT(false, "RendererAPI::None not supported");
            default:
                NEO_CORE_ASSERT(false, "Unknown RendererAPI");
        }
        return nullptr;
    }
}
