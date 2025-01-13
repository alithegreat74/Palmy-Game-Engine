project(Sandbox)

set(CURRENT_DIR ${CMAKE_SOURCE_DIR}/Sandbox)
set(SRC_DIR ${CURRENT_DIR}/src)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported build types" FORCE)

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

add_executable(Sandbox ${SRC_FILES})

include_directories(
    "${CMAKE_SOURCE_DIR}/Palmy"
    "${CMAKE_SOURCE_DIR}/Thirdparty/spdlog/include"
    "${CMAKE_SOURCE_DIR}/Palmy/Thirdparty/glfw/include"
)

if (WIN32)
    target_compile_definitions(Sandbox PRIVATE WINDOWS)
endif()

if (MSVC)
    target_compile_options(Sandbox PRIVATE /utf-8)
endif()

foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG_UPPER)
    if (CONFIG_UPPER STREQUAL "DEBUG")
        target_compile_definitions(Sandbox PRIVATE DEBUG)
        target_compile_options(Sandbox PRIVATE $<$<CONFIG:DEBUG>:-g>)
    elseif (CONFIG_UPPER STREQUAL "RELEASE")
        target_compile_definitions(Sandbox PRIVATE NDEBUG)
        target_compile_options(Sandbox PRIVATE $<$<CONFIG:RELEASE>:-O3>)
    endif()
endforeach()
