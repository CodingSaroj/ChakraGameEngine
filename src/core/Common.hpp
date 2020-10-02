#ifndef CHAKRA_CORE_COMMON_HPP
#define CHAKRA_CORE_COMMON_HPP

#ifdef __WIN32__
    /*
     * #define CHK_PLATFORM     Windows
     */
    #error Windows unsupported.
#elif defined(__linux__)
    #define CHK_PLATFORM     Linux
#elif defined(__APPLE__) && defined(__MACOS__)
    /*
     * #define CHK_PLATFORM MacOS
     */
    #error MacOS unsupported.
#else
    #error Unknown platform.
#endif

#ifdef CHK_GRAPHICS_API
    #if CHK_GRAPHICS_API == OpenGL4
        #define CHK_WINDOW_API GLFW
    #else
        #error Unsupported Graphics API.
    #endif
#else
    #if CHK_PLATFORM == Linux
        #define CHK_GRAPHICS_API OpenGL4
        #define CHK_WINDOW_API GLFW
    #endif
#endif

#ifdef DEBUG
    #ifndef CHK_LOG_LEVEL
        #define CHK_LOG_LEVEL 3
    #endif
#endif

#include "ChakraPCH.hpp"

#endif
