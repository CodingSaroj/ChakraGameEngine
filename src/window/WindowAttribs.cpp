#include "WindowAttribs.hpp"

namespace Chakra
{
    WindowAttribs::WindowAttribs(int width, int height, const std::string & title, bool vsync)
        : Width(width), Height(height), Title(title), VSync(vsync)
    {
    }
}
