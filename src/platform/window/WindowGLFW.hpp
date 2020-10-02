#ifndef CHAKRA_PLATFORM_WINDOW_WINDOW_GLFW_HPP
#define CHAKRA_PLATFORM_WINDOW_WINDOW_GLFW_HPP

#include "core/Common.hpp"

#include "core/Logger.hpp"
#include "core/Event.hpp"
#include "core/EventManager.hpp"

#include "events/WindowEvents.hpp"

#include "window/IWindow.hpp"
#include "window/WindowAttribs.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Chakra
{
    class WindowGLFW : public IWindow
    {
    public:
        explicit WindowGLFW(const WindowAttribs & attribs);
        ~WindowGLFW();

        void Create() override;
        void Update(std::function<void()> updateRoutine) override;

        void * GetRaw() const override;

    private:
        GLFWwindow *        m_Window;
        const WindowAttribs m_Attribs;
    };
}

#endif
