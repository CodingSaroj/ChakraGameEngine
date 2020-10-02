#ifndef CHAKRA_WINDOW_IWINDOW_HPP
#define CHAKRA_WINDOW_IWINDOW_HPP

#include "core/Common.hpp"

namespace Chakra
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        virtual void Create()  = 0;
        virtual void Update(std::function<void()> updateRoutine)  = 0;

        virtual void * GetRaw() const = 0;
    };
}

#endif
