#ifndef CHAKRA_APPLICATION_HPP
#define CHAKRA_APPLICATION_HPP

#include "core/Common.hpp"

#include "core/Logger.hpp"
#include "core/Layer.hpp"
#include "core/LayerStack.hpp"
#include "core/Input.hpp"

#include "core/ecs/Scene.hpp"

#include "window/Window.hpp"

namespace Chakra
{
    class Application : public Layer
    {
        public:
            Application(const WindowAttribs & attribs);
            virtual ~Application() = default;
            
            bool isRunning();

            void setScene(Scene & scene);

            void run();
            void quit();

        protected:
            bool m_Running;

            void OnAttach()         override;
            bool OnEvent(Event * e) override;
            void OnDetach()         override;

            virtual void OnCreate()  = 0;
            virtual void OnUpdate()  = 0;
            virtual void OnDestroy() = 0;

        private:
            Scene  m_CurrentScene;
            Window m_Window;
            Input  m_InputHandler;

        public:
            LayerStack m_LayerStack;
    };
}

#endif
