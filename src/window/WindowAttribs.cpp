#include "WindowAttribs.hpp"

Chakra::WindowAttribs::WindowAttribs(int width, int height, std::string title, bool vsync)
    : Width(width), Height(height), Title(title), VSync(vsync)
{
}
