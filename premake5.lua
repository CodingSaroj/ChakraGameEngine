outputdir = "../../../lib/"

workspace "Chakra"
    configurations
    {
        "Debug",
        "Release"
    }

    platforms
    {
        "Linux32",
        "Linux64"
    }

    include "external/src/GLFW/premake5.lua"

    project "Chakra"
        kind "SharedLib"
        language "C++"
        cppdialect "C++17"

        objdir "obj/%{cfg.system}/%{cfg.buildcfg}/%{cfg.architecture}/"
        targetdir "lib/%{cfg.system}/%{cfg.buildcfg}/%{cfg.architecture}/"

        pchheader "pch/ChakraPCH.hpp"
        pchsource "pch/ChakraPCH.cpp"

        files
        {
            "src/**.cpp"
        }

        includedirs
        {
            "external/src/GLFW/include",
            "external/src/glm/",
            "pch/",
            "src/"
        }

        libdirs
        {
            "external/lib/"
        }

        links
        {
            "GLFW"
        }

        filter "configurations:Debug"
            symbols "On"
            optimize "Off"
            runtime "Debug"

        filter "configurations:Release"
            symbols "Off"
            optimize "Full"
            runtime "Release"
