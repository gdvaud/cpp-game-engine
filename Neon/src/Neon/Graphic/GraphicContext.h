#pragma once

namespace Neon {
    class GraphicContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}  // namespace Neon
