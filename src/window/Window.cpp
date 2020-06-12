#include "Window.hpp"

Chakra::Window::Window(const WindowAttribs & attribs, LayerStack & layerStack)
{
    #if CHK_WINDOW_API == GLFW
        m_Window = new WindowGLFW(attribs, layerStack);
    #endif
}

Chakra::Window::~Window()
{
    delete m_Window;
}

void Chakra::Window::create()
{
    m_Window->create();
}

void Chakra::Window::update()
{
    m_Window->update();
}
