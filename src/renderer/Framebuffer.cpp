#include "Framebuffer.hpp"

namespace Chakra
{
    Framebuffer::Framebuffer()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        m_Framebuffer = new OpenGL4Framebuffer();
    #endif
    }

    Framebuffer::~Framebuffer()
    {
    #if CHK_GRAPHICS_API == OpenGL4
        delete (OpenGL4Framebuffer *)m_Framebuffer;
    #endif
    }

    void Framebuffer::Create(uint64_t width, uint64_t height)
    {
        m_Framebuffer->Create(width, height);
    }

    void Framebuffer::Resize(uint64_t width, uint64_t height)
    {
        m_Framebuffer->Resize(width, height);
    }

    void Framebuffer::Destroy()
    {
        m_Framebuffer->Destroy();
    }

    void Framebuffer::Use()
    {
        m_Framebuffer->Use();
    }

    uint64_t Framebuffer::GetColorAttachment()
    {
        return m_Framebuffer->GetColorAttachment();
    }

    uint64_t Framebuffer::GetWidth()
    {
        return m_Framebuffer->GetWidth();
    }

    uint64_t Framebuffer::GetHeight()
    {
        return m_Framebuffer->GetHeight();
    }
}
