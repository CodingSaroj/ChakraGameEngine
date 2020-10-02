#ifndef CHAKRA_RENDERER_IFRAMEBUFFER_HPP
#define CHAKRA_RENDERER_IFRAMEBUFFER_HPP

#include "core/Common.hpp"

namespace Chakra
{
    class IFrameBuffer
    {
    public:
        virtual ~IFrameBuffer() = default;

        virtual void Create(uint64_t width, uint64_t height) = 0;
        virtual void Resize(uint64_t width, uint64_t height) = 0;
        virtual void Destroy() = 0;

        virtual void Use() = 0;

        virtual uint64_t GetColorAttachment() = 0;

        virtual uint64_t GetWidth() = 0;
        virtual uint64_t GetHeight() = 0;
    };
}

#endif
