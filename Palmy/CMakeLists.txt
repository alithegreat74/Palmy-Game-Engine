project(Engine LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported build types" FORCE)

set(CURRENT_DIR ${CMAKE_SOURCE_DIR}/Palmy)
set(SRC_DIR ${CURRENT_DIR}/src)

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")
file(GLOB IMGUI_FILES
    "${CMAKE_SOURCE_DIR}/Thirdparty/Imgui/*.cpp"
    "${CMAKE_SOURCE_DIR}/Thirdparty/Imgui/*.h"
    "${CMAKE_SOURCE_DIR}/Thirdparty/Imgui/backends/imgui_impl_opengl3_loader.h"
    "${CMAKE_SOURCE_DIR}/Thirdparty/Imgui/backends/imgui_impl_opengl3.h"
    "${CMAKE_SOURCE_DIR}/Thirdparty/Imgui/backends/imgui_impl_opengl3.cpp"
    "${CMAKE_SOURCE_DIR}/Thirdparty/Imgui/backends/imgui_impl_glfw.h"
    "${CMAKE_SOURCE_DIR}/Thirdparty/Imgui/backends/imgui_impl_glfw.cpp"

)
add_library(Engine ${SRC_FILES} ${IMGUI_FILES})

add_subdirectory(${CURRENT_DIR}/Thirdparty/glfw)
add_subdirectory(${CURRENT_DIR}/Thirdparty/glad)
add_subdirectory(${CURRENT_DIR}/Thirdparty/stb_image)
add_subdirectory(${CURRENT_DIR}/Thirdparty/yaml-cpp)

include_directories(
    "${SRC_DIR}"
    "${CURRENT_DIR}/Thirdparty/glfw/include"
    "${CURRENT_DIR}/Thirdparty/glad/include"
    "${CURRENT_DIR}/Thirdparty/stb_image"
    "${CURRENT_DIR}/Thirdparty/yaml-cpp/include"
    "${CMAKE_SOURCE_DIR}/Thirdparty/spdlog/include"
    "${CMAKE_SOURCE_DIR}/Thirdparty/Imgui"
    "${CMAKE_SOURCE_DIR}/Thirdparty/glm/glm"
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

