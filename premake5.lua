workspace "Phoenix"
	architecture "x64"
		startproject "Phoenix"

		configurations
		{
			"Debug",
			"Release",
			"Dist"
		}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Phoenix/vendor/GLFW/include"
IncludeDir["GLAD"] = "Phoenix/vendor/GLAD/include"
IncludeDir["stb_image"] = "Phoenix/vendor/stb_image"
IncludeDir["glm"] = "Phoenix/vendor/glm"
 
-- Include GLFW premake file
include "Phoenix/vendor/GLFW"
include "Phoenix/vendor/GLAD"

project "Phoenix"
	location "Phoenix"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/HAL/**.h",
		"%{prj.name}/HAL/**.cpp",
		"%{prj.name}/Core/**.cpp",
		"%{prj.name}/Core/**.h",
		"%{prj.name}/Phoenix.h",
		"%{prj.name}/Core/Events/**.h",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PHOENIX_PLATFORM_WINDOWS",
			"PHOENIX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		includedirs
		{
		    "%{prj.name}/HAL",
            "%{prj.name}/Core",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.glm}"
		}
		
		links 
		{
		    "GLFW",
		    "GLAD",
		    "opengl32.lib",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}
	filter "configurations:Debug"
	    buildoptions "/MDd"
		defines "PHOENIX_DEBUG"
		symbols "On"
	filter "configurations:Release"
	    buildoptions "/MDd"
		defines "PHOENIX_RELEASE"
		optimize "On"
	filter "configurations:Dist"
	    buildoptions "/MDd"
		defines "PHOENIX_DIST"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/*.h",
		"%{prj.name}/*.cpp"
	}

	includedirs
	{
		"Phoenix/HAL",
		"Phoenix",
		"Phoenix/vendor/spdlog/include",
        "%{IncludeDir.glm}"
	}

	links
	{
		"Phoenix"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PHOENIX_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PHOENIX_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "PHOENIX_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "PHOENIX_DIST"
		optimize "On"

