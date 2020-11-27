#pragma once

#include <vector>

#include "Neon/Core/Base.h"
#include "Neon/Renderer/Buffer.h"

namespace Neon {
    class VertexArray {
    public:
        static Ref<VertexArray> Create();

        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
    };
}  // namespace Neon
