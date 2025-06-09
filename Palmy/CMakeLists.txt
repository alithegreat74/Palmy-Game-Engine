project(Engine LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported build types" FORCE)

set(SRC_DIR "./src")

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")
file(GLOB IMGUI_FILES
    "../Thirdparty/Imgui/*.cpp"
    "../Thirdparty/Imgui/*.h"
    "../Thirdparty/Imgui/backends/imgui_impl_opengl3_loader.h"
    "../Thirdparty/Imgui/backends/imgui_impl_opengl3.h"
    "../Thirdparty/Imgui/backends/imgui_impl_opengl3.cpp"
    "../Thirdparty/Imgui/backends/imgui_impl_glfw.h"
    "../Thirdparty/Imgui/backends/imgui_impl_glfw.cpp"

)
add_library(Engine ${SRC_FILES} ${IMGUI_FILES})

add_subdirectory(./Thirdparty/glfw)
add_subdirectory(./Thirdparty/glad)
add_subdirectory(./Thirdparty/stb_image)
add_subdirectory(./Thirdparty/yaml-cpp)

include_directories(
    "${SRC_DIR}"
    "./Thirdparty/glfw/include"
    "./Thirdparty/glad/include"
    "./Thirdparty/stb_image"
    "./Thirdparty/yaml-cpp/include"
    "../Thirdparty/spdlog/include"
    "../Thirdparty/Imgui"
    "../Thirdparty/glm/glm"
)

target_link_libraries(Engine PUBLIC glfw glad stb_image yaml-cpp)

target_include_directories(Engine PRIVATE ${SRC_DIR})

if (WIN32)
    target_compile_definitions(Engine PRIVATE WINDOWS)
endif()

if (MSVC)
    target_compile_options(Engine PRIVATE /utf-8)
endif()
target_precompile_headers(Engine PRIVATE ${SRC_DIR}/pch.h)

foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG_UPPER)
    if (CONFIG_UPPER STREQUAL "DEBUG")
        target_compile_definitions(Engine PRIVATE DEBUG)
        target_compile_options(Engine PRIVATE $<$<CONFIG:DEBUG>:-g>)
        add_compile_definitions(DEBUG)
    elseif (CONFIG_UPPER STREQUAL "RELEASE")
        target_compile_definitions(Engine PRIVATE NDEBUG)
        target_compile_options(Engine PRIVATE $<$<CONFIG:RELEASE>:-O3>)
    endif()
endforeach()

target_compile_definitions(Engine PRIVATE GLM_ENABLE_EXPERIMENTAL)

