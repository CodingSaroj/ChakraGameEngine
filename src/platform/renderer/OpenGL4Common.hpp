#ifndef CHAKRA_PLATFORM_RENDERER_OPENGL4_COMMON_HPP
#define CHAKRA_PLATFORM_RENDERER_OPENGL4_COMMON_HPP

#include "core/Common.hpp"
#include "core/Logger.hpp"

#include <glad/glad.h>

#ifdef DEBUG
    #define CHK_GL_CALL(functionCall) functionCall; CheckGLError(#functionCall);
#else
    #define CHK_GL_CALL(functionCall) functionCall;
#endif

namespace Chakra
{
    void CheckGLError(const char * functionCall);
}

#endif
