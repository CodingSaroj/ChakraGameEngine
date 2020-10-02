#include "Window.hpp"

namespace Chakra
{
    Window::Window(const WindowAttribs & attribs)
    {
        #if CHK_WINDOW_API == GLFW
            m_Window = new WindowGLFW(attribs);
        #endif
    }
    
    Window::~Window()
    {
        delete m_Window;
    }
    
    void Window::Create()
    {
        m_Window->Create();
    }
    
    void Window::Update(std::function<void()> updateRoutine)
    {
        m_Window->Update(updateRoutine);
    }

    void * Window::GetRaw() const
    {
        return m_Window->GetRaw();
    }
}
