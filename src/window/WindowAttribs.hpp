#ifndef CHAKRA_WINDOW_WINDOW_ATTRIBS_HPP
#define CHAKRA_WINDOW_WINDOW_ATTRIBS_HPP

#include "core/Common.hpp"

namespace Chakra
{
    struct WindowAttribs
    {
        int         Width;
        int         Height;
        std::string Title;
        bool        VSync;

        WindowAttribs(int width, int height, const std::string & title, bool vsync);
    };
}

#endif
