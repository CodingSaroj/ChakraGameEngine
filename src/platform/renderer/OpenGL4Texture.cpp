#include "OpenGL4Texture.hpp"

namespace Chakra
{
    namespace TextureFormat
    {
        uint32_t ChannelRGB = GL_RGB;
        uint32_t ChannelRGBA = GL_RGBA;
        uint32_t ChannelSRGB = GL_SRGB;
        uint32_t ChannelSRGBA = GL_SRGB_ALPHA;

        uint32_t WrapRepeat = GL_REPEAT;
        uint32_t WrapMirroredRepeat = GL_MIRRORED_REPEAT;

        uint32_t FilterLinear = GL_LINEAR;
        uint32_t FilterNearest = GL_NEAREST;
    }

    void OpenGL4Texture::Load(uint32_t width, uint32_t height, TextureData data, std::vector<uint8_t> & pixelData)
    {
        CHK_GL_CALL(glGenTextures(1, &m_TextureHandle));
        CHK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_TextureHandle));
        CHK_GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        CHK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, data.ChannelFormat, width, height, 0, data.ChannelFormat, GL_UNSIGNED_BYTE, pixelData.data()));
        CHK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, data.WrapS));
        CHK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, data.WrapT));
        CHK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, data.MinFilter));
        CHK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, data.MagFilter));
        CHK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void OpenGL4Texture::Unload()
    {
        CHK_GL_CALL(glDeleteTextures(1, &m_TextureHandle));
    }

    void OpenGL4Texture::Use(uint16_t textureIndex)
    {
        glActiveTexture(GL_TEXTURE0 + textureIndex);
        CHK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_TextureHandle));
    }
}
