#ifndef CHAKRA_WINDOW_WINDOW_HPP
#define CHAKRA_WINDOW_WINDOW_HPP

#include "core/Common.hpp"
#include "core/Event.hpp"
#include "core/EventManager.hpp"

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
            explicit Window(const WindowAttribs & attribs);
            ~Window();

            void Create() override;
            void Update(std::function<void()> updateRoutine) override;

            void * GetRaw() const override;

        private:
            IWindow * m_Window;
    };
}

#endif
