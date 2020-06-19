#include "Window.hpp"

namespace Chakra
{
    Window::Window(const WindowAttribs & attribs, LayerStack & layerStack)
    {
        #if CHK_WINDOW_API == GLFW
            m_Window = new WindowGLFW(attribs, layerStack);
        #endif
    }
    
    Window::~Window()
    {
        delete m_Window;
    }
    
    void Window::create()
    {
        m_Window->create();
    }
    
    void Window::update()
    {
        m_Window->update();
    }
}
