workspace "Hazel"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "Hazel"
		location "Hazel"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "hzpch.h"
		pchsource "Hazel/src/hzpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "on"
			systemversion "latest"

			defines
			{
				"HZ_PLATFORM_WINDOWS",
				"HZ_BUILD_DLL",
			}

		filter "configurations:Debug"
			defines "HZ_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			optimize "on"

		filter "configurations:Dist"
			defines "HZ_DIST"
			optimize "on"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
		}

		includedirs
		{
			"Hazel/src",
			"Hazel/vendor/spdlog/include",
		}

		links
		{
			"Hazel"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "on"
			systemversion "latest"

			defines
			{
				"HZ_PLATFORM_WINDOWS",
			}

			postbuildcommands
			{
				("{COPY} ../bin/" .. outputdir .. "/Hazel/Hazel.dll" .. " ../bin/" .. outputdir .. "/%{prj.name}")
			}

		filter "configurations:Debug"
			defines "HZ_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			optimize "on"

		filter "configurations:Dist"
			defines "HZ_DIST"
			optimize "on"
