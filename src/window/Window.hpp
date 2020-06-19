#ifndef CHAKRA_WINDOW_HPP
#define CHAKRA_WINDOW_HPP

#include "core/Common.hpp"
#include "core/Event.hpp"
#include "core/LayerStack.hpp"

#include "window/IWindow.hpp"
#include "window/WindowAttribs.hpp"

#if CHK_WINDOW_API == GLFW
    #include "platform/window/WindowGLFW.hpp"
#endif

namespace Chakra
{
    class Window : public IWindow
    {
        public:
            Window(const WindowAttribs & attribs, LayerStack & layerStack);
            ~Window();

            void create() override;
            void update() override;

        private:
            IWindow * m_Window;
    };
}

#endif
