#include "OpenGL4Framebuffer.hpp"

namespace Chakra
{
    void OpenGL4Framebuffer::Create(uint64_t width, uint64_t height)
    {
        m_Width = width;
        m_Height = height;

        CHK_GL_CALL(glGenFramebuffers(1, &m_FramebufferHandle));
        CHK_GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferHandle));

        CHK_GL_CALL(glGenTextures(1, &m_ColorAttachment));
        CHK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment));

        CHK_GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        CHK_GL_CALL(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
        CHK_GL_CALL(glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0));
        CHK_GL_CALL(glPixelStorei(GL_UNPACK_SKIP_ROWS, 0));
        CHK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
        CHK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        CHK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        CHK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        CHK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        CHK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

        CHK_GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0));

        CHK_GL_CALL(glGenTextures(1, &m_DepthStencilAttachment));
        CHK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_DepthStencilAttachment));
        CHK_GL_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        CHK_GL_CALL(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
        CHK_GL_CALL(glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0));
        CHK_GL_CALL(glPixelStorei(GL_UNPACK_SKIP_ROWS, 0));
        CHK_GL_CALL(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height));
        CHK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

        CHK_GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthStencilAttachment, 0));

        CHK_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Renderer::OpenGL4", "Framebuffer not complete.");

        CHK_GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    void OpenGL4Framebuffer::Resize(uint64_t width, uint64_t height)
    {
        Destroy();

        Create(width, height);
    }

    void OpenGL4Framebuffer::Destroy()
    {
        CHK_GL_CALL(glDeleteTextures(1, &m_ColorAttachment));
        CHK_GL_CALL(glDeleteTextures(1, &m_DepthStencilAttachment));

        CHK_GL_CALL(glDeleteFramebuffers(1, &m_FramebufferHandle));
    }

    void OpenGL4Framebuffer::Use()
    {
        CHK_GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferHandle));
        CHK_GL_CALL(glViewport(0, 0, m_Width, m_Height));
    }

    uint64_t OpenGL4Framebuffer::GetColorAttachment()
    {
        return m_ColorAttachment;
    }

    uint64_t OpenGL4Framebuffer::GetWidth()
    {
        return m_Width;
    }

    uint64_t OpenGL4Framebuffer::GetHeight()
    {
        return m_Height;
    }
}
