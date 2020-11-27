#pragma once

#include "Neon/Renderer/Buffer.h"

namespace Neon {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t count);
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        virtual const BufferLayout& GetLayout() const override { return m_Layout; };
        virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; };

    private:
        uint32_t m_RendererId;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;

        uint32_t GetCount() const override;

    private:
        uint32_t m_RendererId;
        uint32_t m_Count;
    };
}  // namespace Neon
