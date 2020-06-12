#ifndef CHAKRA_IWINDOW_HPP
#define CHAKRA_IWINDOW_HPP

namespace Chakra
{
    class IWindow
    {
        public:
            virtual ~IWindow() = default;

            virtual void create()  = 0;
            virtual void update()  = 0;
    };
}

#endif
