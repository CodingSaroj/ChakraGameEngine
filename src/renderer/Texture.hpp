#ifndef CHAKRA_RENDERER_TEXTURE_HPP
#define CHAKRA_RENDERER_TEXTURE_HPP

#include "core/Common.hpp"

#include "renderer/ITexture.hpp"

#if CHK_GRAPHICS_API == OpenGL4
    #include "platform/renderer/OpenGL4Texture.hpp"
#endif

namespace Chakra
{
    class Texture : public ITexture
    {
    public:
        Texture();
        ~Texture();

        void Load(uint32_t width, uint32_t height, TextureData data, std::vector<uint8_t> & pixelData) override;
        void Unload() override;

        void Use(uint16_t textureIndex) override;

    private:
        ITexture * m_Texture;
    };
}

#endif
