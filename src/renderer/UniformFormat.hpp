#ifndef CHAKRA_RENDERER_UNIFORM_FORMAT_HPP
#define CHAKRA_RENDERER_UNIFORM_FORMAT_HPP

#include "core/Common.hpp"

#include <spirv-cross/spirv_cross.hpp>

namespace Chakra
{
    struct UniformFormat
    {
        spirv_cross::SPIRType Type;
        std::string           Name;
        size_t                Size;

        std::vector<UniformFormat> Members;
    };
}

#endif
