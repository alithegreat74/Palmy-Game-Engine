workspace "Palmy"
    configurations { "Debug", "Release" }
    location "build"
    toolset("gcc")

project "Palmy"
    kind "StaticLib"
    architecture "x64"
    language "C++"
    files { "Palmy/src/**.h", "Palmy/src/**.cpp" }

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
    files { "Sandbox/src/**.h", "Sandbox/src/**.cpp" }
    includedirs {"Palmy/src"}
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"


