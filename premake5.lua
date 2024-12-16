workspace "Palmy"
    configurations { "Debug", "Release" }
    toolset("gcc")

project "Palmy"
    kind "StaticLib"
    architecture "x64"
    language "C++"
    files { "Palmy/src/**.h", "Palmy/src/**.cpp" }
    includedirs {
        "Thirdparty/spdlog/include"
    }
    cppdialect "C++20"

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
    architecture "x64"
    language "C++"
    cppdialect "C++20"
    files { "Sandbox/src/**.h", "Sandbox/src/**.cpp" }
    includedirs {
        "Palmy",
        "Thirdparty/spdlog/include"
    }
    links {"Palmy"}

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


