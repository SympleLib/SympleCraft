workspace "SympleCraft"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Production"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "SympleCraft"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	
	targetdir ("%{wks.location}/bin/" .. outputdir)
	objdir ("%{wks.location}/bin-int/" .. outputdir)
	
	pchheader "pch.h"
	pchsource "src/pch.c"
	
	files {
		"src/**.h",
		"src/**.c",
		"src/**.hpp",
		"src/**.cpp"
	}
	
	includedirs {
		"src",
		"vender/GLFW/include",
		"vender/GLEW/include"
	}
	
	links {
		"MSVCRT",
		"MSVCRTD",
		"opengl32",
		"gdi32",
		"libcmt",
		"vender/GLEW/lib/Release/x64/glew32s",
		"vender/GLFW/lib-vc2019/glfw3"
	}
	
	defines "GLEW_STATIC"
	
	filter "configurations:Debug"
		defines "_SY_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "_SY_RELEASE"
		optimize "On"

	filter "configurations:Production"
		defines "_SY_PRODUCTION"
		optimize "On"