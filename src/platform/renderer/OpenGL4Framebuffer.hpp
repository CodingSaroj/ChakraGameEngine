#ifndef CHAKRA_PLATFORM_RENDERER_OPENGL4_FRAMEBUFFER_HPP
#define CHAKRA_PLATFORM_RENDERER_OPENGL4_FRAMEBUFFER_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"

#include "renderer/IFramebuffer.hpp"

#include "platform/renderer/OpenGL4Common.hpp"

#include <glad/glad.h>

namespace Chakra
{
    class OpenGL4Framebuffer : public IFrameBuffer
    {
    public:
        void Create(uint64_t width, uint64_t height) override;
        void Resize(uint64_t width, uint64_t height) override;
        void Destroy() override;

        void Use() override;
        
        uint64_t GetColorAttachment() override;

        uint64_t GetWidth() override;
        uint64_t GetHeight() override;

    private:
        GLuint m_FramebufferHandle;
        GLuint m_ColorAttachment, m_DepthStencilAttachment;

        uint64_t m_Width;
        uint64_t m_Height;
    };
}

#endif
