project "glad"
	kind "StaticLib"
	language "C"
	cdialect "C11"
	targetdir "%{TargetLibDir}/"
    objdir "obj/%{cfg.buildcfg}/%{cfg.platform}/"
	
	pic "On"
	
	files
	{
		"../src/glad/src/glad.c"
	}
	
	includedirs
	{
		"../src/glad/include/"
	}
	
	postbuildcommands
    {
        "{MKDIR} %{TargetIncludeDir}/glad",
        "{COPY} ../src/glad/include/glad/glad.h %{TargetIncludeDir}/glad/glad.h"
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
