#pragma once

#include "Neon/Renderer/Buffer.h"

namespace Neon {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t count);
        virtual ~OpenGLVertexBuffer();
        
        void Bind() const override;
        void Unbind() const override;
        
    private:
        uint32_t _rendererId;
    };
    
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();
        
        void Bind() const override;
        void Unbind() const override;
    
        uint32_t GetCount() const override;
        
    private:
        uint32_t _rendererId;
        uint32_t _count;
    };
}
