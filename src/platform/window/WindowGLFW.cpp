#include "WindowGLFW.hpp"

#include "core/Application.hpp"

namespace Chakra
{
    WindowGLFW::WindowGLFW(const WindowAttribs & attribs)
        : m_Attribs(attribs), m_Window(nullptr)
    {
    }
    
    WindowGLFW::~WindowGLFW()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    static void resizeCallback(GLFWwindow * window, int width, int height)
    {
        Application::GetApplication().GetEventManager().Propagate(WindowResizeEvent(width, height));
    }
    
    static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mod)
    {
        if (action == GLFW_PRESS)
        {
            Application::GetApplication().GetEventManager().Propagate(KeyPressEvent(key, mod));
        }
        else if (action == GLFW_RELEASE)
        {
            Application::GetApplication().GetEventManager().Propagate(KeyReleaseEvent(key, mod));
        }
    }

    static void charCallback(GLFWwindow * window, unsigned int unicodeChar)
    {
        Application::GetApplication().GetEventManager().Propagate(KeyTypeEvent(unicodeChar));
    }
    
    static void mouseButtonCallback(GLFWwindow * window, int button, int action, int mod)
    {
        if (action == GLFW_PRESS)
        {
            Application::GetApplication().GetEventManager().Propagate(MouseButtonPressEvent(button, mod));
        }
        else if (action == GLFW_RELEASE)
        {
            Application::GetApplication().GetEventManager().Propagate(MouseButtonReleaseEvent(button, mod));
        }
    }
    
    static void scrollCallback(GLFWwindow * window, double x, double y)
    {
        Application::GetApplication().GetEventManager().Propagate(ScrollEvent(x, y));
    }
    
    static void cursorCallback(GLFWwindow * window, double x, double y)
    {
        Application::GetApplication().GetEventManager().Propagate(MouseMoveEvent(x, y));
    }
    
    void WindowGLFW::Create()
    {
        glfwInit();
    
        glfwWindowHint(GLFW_RESIZABLE,              GLFW_TRUE);
        glfwWindowHint(GLFW_DOUBLEBUFFER,           GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE,         GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,  4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,  5);
    
        m_Window = glfwCreateWindow(m_Attribs.Width, m_Attribs.Height, m_Attribs.Title.c_str(), nullptr, nullptr);

        CHK_ASSERT(m_Window, "Window::GLFW", "Unable to create GLFW window.")
    
        glfwMakeContextCurrent(m_Window);

        CHK_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Window::GLFW", "Failed to initialize GLAD.");
    
        glfwSetFramebufferSizeCallback(m_Window, resizeCallback);
        glfwSetKeyCallback(m_Window, keyCallback);
        glfwSetCharCallback(m_Window, charCallback);
        glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
        glfwSetCursorPosCallback(m_Window, cursorCallback);
        glfwSetScrollCallback(m_Window, scrollCallback);
    
        glfwSetWindowUserPointer(m_Window, this);
    }
    
    void WindowGLFW::Update(std::function<void()> updateRoutine)
    {
        if (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();

            updateRoutine();

            Application::GetApplication().GetEventManager().Propagate(ImGuiRenderEvent());
    	
            glfwSwapBuffers(m_Window);
        }
        else
        {
            Application::GetApplication().GetEventManager().Propagate(WindowDestroyEvent());
        }
    }

    void * WindowGLFW::GetRaw() const
    {
        return (void *)m_Window;
    }
}
