workspace "Chakra"
    configurations
    {
        "Debug",
        "Release"
    }

    platforms
    {
        "Windows32",
        "Windows64",
        "Linux32",
        "Linux64"
    }

    include "external/premake5.lua"

    project "CHKMesh"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        targetname "chkmesh"
        targetdir "bin/%{cfg.buildcfg}/%{cfg.platform}/"

        files
        {
            "tools/CHKMesh.cpp"
        }

        includedirs
        {
            "src",
            "pch",
            "external/include"
        }

        libdirs
        {
            "external/lib"
        }

        links
        {
            "assimp"
        }

        filter "configurations:Debug"
            symbols "On"
            optimize "Off"

            defines
            {
                "DEBUG"
            }

        filter "configurations:Release"
            symbols "Off"
            optimize "Full"

        filter "platforms:*32"
            architecture "x86"

        filter "platforms:*64"
            architecture "x86_64"

        filter "platforms:Windows*"
            system "windows"

        filter "platforms:Linux*"
            system "linux"

    project "Chakra"
        kind "SharedLib"
        language "C++"
        cppdialect "C++17"
        targetdir "lib/%{cfg.buildcfg}/%{cfg.platform}/"

        files
        {
            "external/src/imgui/examples/imgui_impl_glfw.cpp",
            "external/src/imgui/examples/imgui_impl_opengl3.cpp",
            "src/**.hpp",
            "src/**.cpp"
        }

        pchheader "pch/ChakraPCH.hpp"
        pchsource "pch/ChakraPCH.cpp"

        includedirs
        {
            "src/",
            "pch/",
            "external/include",
            "external/include/imgui/"
        }

        libdirs
        {
            "external/lib"
        }

        links
        {
            "imgui",
            "implot",
            "yaml-cpp",
        	"glad",
            "spirv-cross-core",
            "spirv-cross-reflect",
            "spirv-cross-util",
            "spirv-cross-glsl",
            "glfw3"
        }

        filter "configurations:Debug"
            symbols "On"
            optimize "Off"

            defines
            {
                "DEBUG"
            }

        filter "configurations:Release"
            symbols "Off"
            optimize "Full"

        filter "platforms:*32"
            architecture "x86"

        filter "platforms:*64"
            architecture "x86_64"

        filter "platforms:Windows*"
            system "windows"

            links
            {
                "opengl32"
            }

        filter "platforms:Linux*"
            system "linux"

            links
            {
                "GL"
            }

    project "ChakraEditor"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        targetdir "bin/%{cfg.buildcfg}/%{cfg.platform}"

        files
        {
            "editor/*.cpp"
        }

        includedirs
        {
            "src/",
            "pch/",
            "external/include",
            "external/include/imgui/"
        }

        libdirs
        {
            "lib/%{cfg.buildcfg}/%{cfg.system}"
        }

        links
        {
            "Chakra",
            "z"
        }
        
        filter "configurations:Debug"
            symbols "On"
            optimize "Off"

            defines
            {
                "DEBUG"
            }

        filter "configurations:Release"
            symbols "Off"
            optimize "Full"

        filter "platforms:*32"
            architecture "x86"

        filter "platforms:*64"
            architecture "x86_64"

        filter "platforms:Linux*"
            system "linux"

            links
            {
                "dl",
                "pthread"
            }

    project "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        targetdir "bin/%{cfg.buildcfg}/%{cfg.platform}"

        files
        {
            "test/main.cpp"
        }

        includedirs
        {
            "src/",
            "pch/",
            "external/include",
            "external/include/imgui/"
        }

        libdirs
        {
            "lib/%{cfg.buildcfg}/%{cfg.system}"
        }

        links
        {
            "Chakra",
            "z"
        }
        
        filter "configurations:Debug"
            symbols "On"
            optimize "Off"

            defines
            {
                "DEBUG"
            }

        filter "configurations:Release"
            symbols "Off"
            optimize "Full"

        filter "platforms:*32"
            architecture "x86"

        filter "platforms:*64"
            architecture "x86_64"

        filter "platforms:Linux*"
            system "linux"

            links
            {
                "dl",
                "pthread"
            }
