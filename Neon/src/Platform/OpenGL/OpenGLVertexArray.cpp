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
        glCreateVertexArrays(1, &m_RendererId);
    }
    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_RendererId);
    }

    void OpenGLVertexArray::Bind() const { glBindVertexArray(m_RendererId); }
    void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        NEO_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout set");

        glBindVertexArray(m_RendererId);
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

        m_VertexBuffers.push_back(vertexBuffer);
    }
    void OpenGLVertexArray::SetIndexBuffer(
        const Ref<IndexBuffer>& indexBuffer) {
        glBindVertexArray(m_RendererId);

        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}  // namespace Neon
