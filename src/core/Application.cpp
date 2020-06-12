#include "Application.hpp"

Chakra::Application::Application(const WindowAttribs & attribs)
    : m_Running(false), m_CurrentScene(""), m_Window(attribs, m_LayerStack)
{
    m_LayerStack.push(this);
    m_LayerStack.push(&m_InputHandler);
}

bool Chakra::Application::isRunning()
{
    return m_Running;
}

void Chakra::Application::setScene(Scene & scene)
{
    m_CurrentScene = scene;
}

void Chakra::Application::run()
{
    OnCreate();
    m_Window.create();
    m_CurrentScene.Initialize();

    m_Running = true;

    while (m_Running)
    {
        OnUpdate();
        m_CurrentScene.Update();
        m_Window.update();

        m_InputHandler.clear();
    }

    OnDestroy();
    m_CurrentScene.Exit();
}

void Chakra::Application::quit()
{
    m_Running = false;
}

void Chakra::Application::OnAttach()
{
}

bool Chakra::Application::OnEvent(Event * e)
{
    if (e->getType() == EventType::OnClose)
    {
        this->quit();
        return true;
    }
    else
    {
        return false;
    }
}

void Chakra::Application::OnDetach()
{
}
