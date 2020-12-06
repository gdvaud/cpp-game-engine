#pragma once
#include <string>

#include "Neon/Graphic/Texture.h"

namespace Neon {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

        void Bind(uint32_t slot) const override;

        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }

    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererId;
    };
}  // namespace Neon
