project "imgui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "%{TargetLibDir}/"
    objdir "obj/%{cfg.buildcfg}/%{cfg.platform}/"
	
	pic "On"
	
	files
	{
		"../src/imgui/*.h",
		"../src/imgui/*.cpp",
	}
	
	includedirs
	{
		"../src/imgui/"
	}
	
	postbuildcommands
    {
        "{MKDIR} %{TargetIncludeDir}/imgui",
        "{COPY} ../src/imgui/*.h %{TargetIncludeDir}/imgui",
        "{COPY} ../src/imgui/examples/imgui_impl_glfw.h %{TargetIncludeDir}/imgui/imgui_impl_glfw.h",
        "{COPY} ../src/imgui/examples/imgui_impl_opengl3.h %{TargetIncludeDir}/imgui/imgui_impl_opengl3.h"
    }
	
	filter "configurations:Debug"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        symbols "Off"
        optimize "Full"
        
        defines
        {
            "NDEBUG"
        }

    filter "platforms:*32"
        architecture "x86"

    filter "platforms:*64"
        architecture "x86_64"

    filter "platforms:Windows*"
        system "windows"
        
    filter "platforms:Linux*"
        system "linux"
