#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Neon {
    class RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1,
        };

    public:
        inline static API GetAPI() { return _api; }

    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

    private:
        static API _api;
    };
}  // namespace Neon
