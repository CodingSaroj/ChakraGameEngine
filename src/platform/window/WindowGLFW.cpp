#include "WindowGLFW.hpp"

namespace Chakra
{
    WindowGLFW::WindowGLFW(const WindowAttribs & attribs, LayerStack & layerStack)
        : m_Attribs(attribs), m_LayerStack(layerStack)
    {
    }
    
    WindowGLFW::~WindowGLFW()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
    
    static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mod)
    {
        WindowGLFW & win = *(WindowGLFW *)glfwGetWindowUserPointer(window);
    
        if (action == GLFW_PRESS)
        {
            win.send(KeyPressEvent(key, mod));
        }
        else if (action == GLFW_RELEASE)
        {
            win.send(KeyReleaseEvent(key, mod));
        }
    }
    
    static void mouseButtonCallback(GLFWwindow * window, int button, int action, int mod)
    {
        WindowGLFW & win = *(WindowGLFW *)glfwGetWindowUserPointer(window);
        
        if (action == GLFW_PRESS)
        {
            win.send(MouseButtonPressEvent(button, mod));
        }
        else if (action == GLFW_RELEASE)
        {
            win.send(MouseButtonReleaseEvent(button, mod));
        }
    }
    
    static void scrollCallback(GLFWwindow * window, double x, double y)
    {
        WindowGLFW & win = *(WindowGLFW *)glfwGetWindowUserPointer(window);
    
        win.send(ScrollEvent(x, y));
    }
    
    static void cursorCallback(GLFWwindow * window, double x, double y)
    {
        WindowGLFW & win = *(WindowGLFW *)glfwGetWindowUserPointer(window);
    
        win.send(MouseMoveEvent(x, y));
    }
    
    void WindowGLFW::send(Event && e)
    {
        m_LayerStack.propagate(std::move(e));
    }
    
    void WindowGLFW::create()
    {
        glfwInit();
    
        glfwWindowHint(GLFW_RESIZABLE,              GLFW_FALSE);
        glfwWindowHint(GLFW_DOUBLEBUFFER,           GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,  3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,  3);
    
        m_Window = glfwCreateWindow(m_Attribs.Width, m_Attribs.Height, m_Attribs.Title.c_str(), nullptr, nullptr);
    
        if (!m_Window)
        {
            Logger::LogError("Window::GLFW", "Unable to create GLFW window");
            exit(-1);
        }
    
        glfwMakeContextCurrent(m_Window);
    
        glfwSetKeyCallback         (m_Window, keyCallback);
        glfwSetMouseButtonCallback (m_Window, mouseButtonCallback);
        glfwSetCursorPosCallback   (m_Window, cursorCallback);
        glfwSetScrollCallback      (m_Window, scrollCallback);
    
        glfwSetWindowUserPointer(m_Window, this);
    }
    
    void WindowGLFW::update()
    {
        if (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();
    
            glfwSwapBuffers(m_Window);
        }
        else
        {
            this->send(CloseEvent());
        }
    }
}
