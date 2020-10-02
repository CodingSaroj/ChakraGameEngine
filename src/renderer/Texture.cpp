#include "Texture.hpp"

namespace Chakra
{
    Texture::Texture()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        m_Texture = new OpenGL4Texture();
    #endif
    }
    
    Texture::~Texture()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        delete (OpenGL4Texture *)m_Texture;
    #endif
    }

    void Texture::Load(uint32_t width, uint32_t height, TextureData data, std::vector<uint8_t> & pixelData)
    {
        m_Texture->Load(width, height, data, pixelData);
    }

    void Texture::Unload()
    {
        m_Texture->Unload();
    }

    void Texture::Use(uint16_t textureIndex)
    {
        m_Texture->Use(textureIndex);
    }
}
