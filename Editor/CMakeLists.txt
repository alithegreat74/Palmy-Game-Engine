project(Editor)

# Define paths
set(SRC_DIR ./src)

# Find all source files
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

# Create the Editor executable
add_executable(Editor ${SRC_FILES})

# Include directories
include_directories(
    "../Palmy"
    "../Thirdparty/spdlog/include"
    "../Palmy/Thirdparty/glfw/include"
    "../Palmy/Thirdparty/glad/include"
    "../Palmy/Thirdparty/yaml-cpp/include"
    "../Thirdparty/glm/glm"

)

# Platform-specific settings
if (WIN32)
    target_compile_definitions(Editor PRIVATE WINDOWS)
endif()

# Compiler-specific settings
if (MSVC)
    target_compile_options(Editor PRIVATE /utf-8)
endif()

# Debug/Release settings
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Editor PRIVATE DEBUG)
    target_compile_options(Editor PRIVATE $<$<CONFIG:DEBUG>:-g>)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Editor PRIVATE NDEBUG)
    target_compile_options(Editor PRIVATE $<$<CONFIG:RELEASE>:-O3>)
endif()

# Define the source and destination for the Assets folder copy
set(ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR}/Editor/Assets)

# Add a custom command to copy the Assets folder after the Editor target is built
add_custom_command(
    TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_SOURCE_DIR} ${ASSETS_DEST_DIR}
    COMMENT "Copying Assets folder to build directory"
)

# Debugging information
message("ASSETS_SOURCE_DIR: ${ASSETS_SOURCE_DIR}")
message("ASSETS_DEST_DIR: ${ASSETS_DEST_DIR}")
