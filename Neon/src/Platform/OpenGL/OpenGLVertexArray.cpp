#include "OpenGLVertexArray.h"

namespace Neon {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case Neon::ShaderDataType::Float:
            case Neon::ShaderDataType::Float2:
            case Neon::ShaderDataType::Float3:
            case Neon::ShaderDataType::Float4:
            case Neon::ShaderDataType::Mat3:
            case Neon::ShaderDataType::Mat4:
                return GL_FLOAT;
            case Neon::ShaderDataType::Int:
            case Neon::ShaderDataType::Int2:
            case Neon::ShaderDataType::Int3:
            case Neon::ShaderDataType::Int4:
                return GL_INT;
            case Neon::ShaderDataType::Bool:
                return GL_BOOL;
        }

        NEO_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &_rendererID);
    }
    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &_rendererID);
    }

    void OpenGLVertexArray::Bind() const { glBindVertexArray(_rendererID); }
    void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        NEO_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout set");

        glBindVertexArray(_rendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void*)element.Offset);
            index++;
        }

        _vertexBuffers.push_back(vertexBuffer);
    }
    void OpenGLVertexArray::SetIndexBuffer(
        const Ref<IndexBuffer>& indexBuffer) {
        glBindVertexArray(_rendererID);

        indexBuffer->Bind();

        _indexBuffer = indexBuffer;
    }
}  // namespace Neon
