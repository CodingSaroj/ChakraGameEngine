#ifndef CHAKRA_CORE_APPLICATION_HPP
#define CHAKRA_CORE_APPLICATION_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"
#include "core/Time.hpp"
#include "core/Profiler.hpp"
#include "core/Listener.hpp"
#include "core/EventManager.hpp"
#include "core/Input.hpp"
#include "core/ImGuiListener.hpp"

#include "scene/Scene.hpp"

#include "window/Window.hpp"

namespace Chakra
{
    class Application : public Listener
    {
    public:
        static Application & Instance(Application * application);
        static Application & GetApplication();

        explicit Application(const WindowAttribs & attribs);
        
        bool IsRunning();

        void Run();
        void Quit();

        constexpr const Window & GetWindow() const { return m_Window; }
        constexpr EventManager & GetEventManager() { return m_EventManager;}

    protected:
        bool m_Running;

        Scene m_Scene;

        EventManager  m_EventManager;
        Window        m_Window;
        ImGuiListener m_ImGuiListener;
        Input         m_InputHandler;

        bool OnEvent(Event * e) override;

        virtual void OnCreate();
        virtual void OnUpdate();
        virtual void OnDestroy();
        virtual void OnResize(int width, int height);
        virtual void OnImGuiRender();

    private:
        static Application * s_Application;
    };
}

#endif
