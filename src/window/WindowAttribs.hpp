#ifndef CHAKRA_WINDOW_ATTRIBS_HPP
#define CHAKRA_WINDOW_ATTRIBS_HPP

#include <iostream>

namespace Chakra
{
    struct WindowAttribs
    {
        int         Width;
        int         Height;
        std::string Title;
        bool        VSync;

        WindowAttribs(int width, int height, std::string title, bool vsync);
    };
}

#endif
