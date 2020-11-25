#pragma once

#include "Neon/Renderer/Buffer.h"

namespace Neon {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t count);
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        virtual const BufferLayout& GetLayout() const override { return _layout; };
        virtual void SetLayout(const BufferLayout& layout) { _layout = layout; };

    private:
        uint32_t _rendererId;
        BufferLayout _layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;

        uint32_t GetCount() const override;

    private:
        uint32_t _rendererId;
        uint32_t _count;
    };
}  // namespace Neon
