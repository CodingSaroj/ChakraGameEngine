#ifndef CHAKRA_PLATFORM_RENDERER_OPENGL4_TEXTURE_HPP
#define CHAKRA_PLATFORM_RENDERER_OPENGL4_TEXTURE_HPP

#include "core/Common.hpp"

#include "renderer/ITexture.hpp"

#include "platform/renderer/OpenGL4Common.hpp"

#include <glad/glad.h>

namespace Chakra
{
    class OpenGL4Texture : public ITexture
    {
    public:
        void Load(uint32_t width, uint32_t height, TextureData data, std::vector<uint8_t> & pixelData) override;
        void Unload() override;

        void Use(uint16_t textureIndex) override;

    private:
        GLuint m_TextureHandle;
    };
}

#endif
