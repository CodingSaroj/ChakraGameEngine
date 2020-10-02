project "implot"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "%{TargetLibDir}/"
    objdir "obj/%{cfg.buildcfg}/%{cfg.platform}/"
	
	pic "On"
	
	files
	{
		"../src/implot/*.h",
		"../src/implot/*.cpp"
	}
	
	includedirs
	{
	    "../src/imgui",
		"../src/implot"
	}
	
	postbuildcommands
    {
        "{MKDIR} %{TargetIncludeDir}/implot",
        "{COPY} ../src/implot/*.h %{TargetIncludeDir}/implot",
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
