workspace "Palmy"
    configurations { "Debug", "Release" }
    toolset("gcc")
    architecture "x64"
    startproject "Sandbox"

include "Palmy/Thirdparty/glfw"

project "Palmy"
    kind "StaticLib"
    language "C++"
    files { 
        "Palmy/src/**.h",
        "Palmy/src/**.cpp",
        "Palmy/Palmy.h"
    }
    cppdialect "C++20"
    
    includedirs {
        "Palmy/src",
        "Thirdparty/spdlog/include",
        "Palmy/Thirdparty/glfw/include"
    }
    links {
        "GLFW"
    }
    filter "action:vs*"
        buildoptions { "/utf-8" }
    filter {"system:Windows"}
        defines {"WINDOWS"}

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    files { "Sandbox/src/**.h", "Sandbox/src/**.cpp" }
    includedirs {
        "Palmy",
        "Thirdparty/spdlog/include",
        "Palmy/Thirdparty/glfw/include"
    }
    links {
        "Palmy",
        "GLFW"
    }

    filter "action:vs*"
        buildoptions { "/utf-8" }
    filter {"system:Windows"}
        defines {"WINDOWS"}
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"


