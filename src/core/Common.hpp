#ifndef CHAKRA_COMMON_HPP
#define CHAKRA_COMMON_HPP

#ifdef __WIN32__
    /*
     * #define CHK_PLATFORM     Windows
     * #define CHK_WINDOW_API   Win32
     * #define CHK_GRAPHICS_API DirectX
     * #define CHK_AUDIO_API    DSound
     */
    #error Unsupported platform!
#elif defined(__linux__)
    #define CHK_PLATFORM     Linux
    #define CHK_WINDOW_API   GLFW
    #define CHK_GRAPHICS_API OpenGL
    #define CHK_AUDIO_API    OpenAL
#elif defined(__APPLE__) && defined(__MACOS__)
    /*
     * #define CHK_PLATFORM MacOS
     * #define CHK_WINDOW_API   Cocoa
     * #define CHK_GRAPHICS_API Metal
     * #define CHK_AUDIO_API    OpenAL
     */
    #error Unsupported platform!
#else
    #error Unsupported platform!
#endif

#ifndef CHK_LOG_LEVEL
    #define CHK_LOG_LEVEL 3
#endif

#include "ChakraPCH.hpp"

#endif
