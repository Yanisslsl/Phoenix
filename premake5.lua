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
		"%{prj.name}/Phoenix.h"

	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PHOENIX_PLATFORM_WINDOWS",
			"PHOENIX_BUILD_DLL"
		}
		
		includedirs
		{
			"%{prj.name}/vendor/spdlog/include",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
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
	}

	links
	{
		"Phoenix"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
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

