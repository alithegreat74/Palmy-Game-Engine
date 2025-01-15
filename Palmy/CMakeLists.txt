project(Engine LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported build types" FORCE)

set(CURRENT_DIR ${CMAKE_SOURCE_DIR}/Palmy)
set(SRC_DIR ${CURRENT_DIR}/src)

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

add_library(Engine ${SRC_FILES})

add_subdirectory(${CURRENT_DIR}/Thirdparty/glfw)
add_subdirectory(${CURRENT_DIR}/Thirdparty/glad)

include_directories(
    "${SRC_DIR}"
    "${CURRENT_DIR}/Thirdparty/glfw/include"
    "${CURRENT_DIR}/Thirdparty/glad/include"
    "${CMAKE_SOURCE_DIR}/Thirdparty/spdlog/include"
)

target_link_libraries(Engine PUBLIC glfw glad)

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
    elseif (CONFIG_UPPER STREQUAL "RELEASE")
        target_compile_definitions(Engine PRIVATE NDEBUG)
        target_compile_options(Engine PRIVATE $<$<CONFIG:RELEASE>:-O3>)
    endif()
endforeach()

