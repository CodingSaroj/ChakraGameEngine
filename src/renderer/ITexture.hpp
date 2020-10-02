#ifndef CHAKRA_RENDERER_ITEXTURE_HPP
#define CHAKRA_RENDERER_ITEXTURE_HPP

#include "core/Common.hpp"

namespace Chakra
{
    namespace TextureFormat
    {
        extern uint32_t ChannelRGB;
        extern uint32_t ChannelRGBA;
        extern uint32_t ChannelSRGB;
        extern uint32_t ChannelSRGBA;

        extern uint32_t WrapRepeat;
        extern uint32_t WrapMirroredRepeat;

        extern uint32_t FilterLinear;
        extern uint32_t FilterNearest;
    }

    struct TextureData
    {
        uint32_t ChannelFormat;

        uint32_t WrapS;
        uint32_t WrapT;

        uint32_t MinFilter;
        uint32_t MagFilter;
    };

    class ITexture
    {
    public:
        virtual ~ITexture() = default;

        virtual void Load(uint32_t width, uint32_t height, TextureData data, std::vector<uint8_t> & pixelData) = 0;
        virtual void Unload() = 0;

        virtual void Use(uint16_t textureIndex) = 0;
    };
}

#endif
