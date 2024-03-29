#include "OpenGLTexture.h"

#include <stb_image.h>

namespace Neon {
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
        // Load texture from path
        int width, height, channels;
        //        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        //        NEO_CORE_ASSERT(data, "Failed to load image")
        NEO_CORE_ASSERT(data, stbi_failure_reason())

        m_Width = width;
        m_Height = height;

        // Give texture to OpenGL
        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        if (channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        NEO_CORE_ASSERT(internalFormat & dataFormat, "Unsupported texture format");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
        glTextureStorage2D(m_RendererId, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &m_RendererId); }

    void OpenGLTexture2D::Bind(uint32_t slot) const { glBindTextureUnit(slot, m_RendererId); }
}  // namespace Neon