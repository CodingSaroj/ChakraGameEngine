#ifndef CHAKRA_RENDERER_FRAMEBUFFER_HPP
#define CHAKRA_RENDERER_FRAMEBUFFER_HPP

#include "core/Common.hpp"

#include "renderer/IFramebuffer.hpp"

#if CHK_GRAPHICS_API == OpenGL4
    #include "platform/renderer/OpenGL4Framebuffer.hpp"
#endif

namespace Chakra
{
    class Framebuffer : public IFrameBuffer
    {
    public:
        Framebuffer();
        ~Framebuffer();

        void Create(uint64_t width, uint64_t height) override;
        void Resize(uint64_t width, uint64_t height) override;
        void Destroy() override;

        void Use() override;

        uint64_t GetColorAttachment() override;

        uint64_t GetWidth() override;
        uint64_t GetHeight() override;

    private:
        IFrameBuffer * m_Framebuffer;
    };
}

#endif
