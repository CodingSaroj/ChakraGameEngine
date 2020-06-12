#ifndef CHAKRA_WINDOW_GLFW_HPP
#define CHAKRA_WINDOW_GLFW_HPP

#include <functional>

#include <GLFW/glfw3.h>

#include "core/Logger.hpp"
#include "core/Event.hpp"
#include "core/LayerStack.hpp"

#include "events/WindowEvents.hpp"

#include "window/IWindow.hpp"
#include "window/WindowAttribs.hpp"

namespace Chakra
{
    class WindowGLFW : public IWindow
    {
        public:
            WindowGLFW(const WindowAttribs & attribs, LayerStack & layerStack);
            ~WindowGLFW();

            void send(Event && e);

            void create() override;
            void update() override;

        private:
            GLFWwindow *        m_Window;
            const WindowAttribs m_Attribs;
            LayerStack &        m_LayerStack;
    };
}

#endif
