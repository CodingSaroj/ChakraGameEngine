#include "Application.hpp"

void * operator new(size_t size)
{
    using namespace Chakra;

    s_ProfilerStats.MemoryUsage += size;
    return malloc(size);
}

void operator delete(void * data, size_t size) noexcept
{
    using namespace Chakra;

    s_ProfilerStats.MemoryUsage -= size;
    free(data);
}

namespace Chakra
{
    Application * Application::s_Application;

    Application & Application::Instance(Application * application)
    {
        s_Application = application;

        return *s_Application;
    }

    Application & Application::GetApplication()
    {
        return *s_Application;
    }

    Application::Application(const WindowAttribs & attribs)
        : m_Running(false), m_Window(attribs)
    {
            }
    
    bool Application::IsRunning()
    {
        return m_Running;
    }
    
    void Application::Run()
    {
        m_Window.Create();

        m_EventManager.Push(&m_ImGuiListener);
        m_EventManager.Push(this);
        m_EventManager.Push(&m_InputHandler);

        OnCreate();
        m_Scene.OnCreate();
    
        m_Running = true;

        double counter = 0.0;
    
        while (m_Running)
        {
            auto start = std::chrono::steady_clock::now();

            m_Window.Update([&](){ OnUpdate(); m_Scene.OnUpdate(); });
    
            m_InputHandler.Clear();

            auto end = std::chrono::steady_clock::now();
            auto duration = end - start;

            counter += duration.count();

            if (counter >= 100000000.0)
            {
                counter = 0.0;
                s_ProfilerStats.FrameTime = duration.count() / 1000000.0;
                Time::DeltaTime = s_ProfilerStats.FrameTime;
                s_ProfilerStats.FPS = 1000.0 / s_ProfilerStats.FrameTime;
            }
        }

        OnDestroy();
        m_Scene.OnDestroy();
    }
    
    void Application::Quit()
    {
        m_Running = false;
    }
    
    bool Application::OnEvent(Event * e)
    {
        if (e->Type() == EventType::OnWindowDestroy)
        {
            Quit();
            return true;
        }
        else if (e->Type() == EventType::OnImGuiRender)
        {
            OnImGuiRender();

            m_EventManager.Propagate(ImGuiRenderEvent());

            return true;
        }
        else if (e->Type() == EventType::OnWindowResize)
        {
            auto resizeEvent = (WindowResizeEvent *)e;
            OnResize(resizeEvent->GetWidth(), resizeEvent->GetHeight());
            return true;
        }
        else
        {
            return false;
        }
    }
}
