include "conanbuildinfo.premake.lua"

workspace "Chakra"
    conan_basic_setup()

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

    project "Chakra"
        kind "SharedLib"
        language "C++"
        cppdialect "C++17"
        targetdir "lib/%{cfg.system}/%{cfg.buildcfg}/%{cfg.architecture}/"

        files
        {
            "src/**.cpp"
        }

        includedirs
        {
            conan_includedirs,
            "src/"
        }

        libdirs
        {
            conan_linkdirs
        }

        links
        {
            conan_libs
        }

        linkoptions
        {
            conan_exelinkflags
        }

        filter "configurations:Debug"
            symbols "On"
            optimize "Off"

        filter "configurations:Release"
            symbols "Off"
            optimize "Full"
