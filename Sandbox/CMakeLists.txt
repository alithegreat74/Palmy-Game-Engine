project(Sandbox)

# Define paths
set(CURRENT_DIR ${CMAKE_SOURCE_DIR}/Sandbox)
set(SRC_DIR ${CURRENT_DIR}/src)

# Find all source files
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

# Create the Sandbox executable
add_executable(Sandbox ${SRC_FILES})

# Include directories
include_directories(
    "${CMAKE_SOURCE_DIR}/Palmy"
    "${CMAKE_SOURCE_DIR}/Thirdparty/spdlog/include"
    "${CMAKE_SOURCE_DIR}/Palmy/Thirdparty/glfw/include"
    "${CMAKE_SOURCE_DIR}/Palmy/Thirdparty/glad/include"
)

# Platform-specific settings
if (WIN32)
    target_compile_definitions(Sandbox PRIVATE WINDOWS)
endif()

# Compiler-specific settings
if (MSVC)
    target_compile_options(Sandbox PRIVATE /utf-8)
endif()

# Debug/Release settings
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Sandbox PRIVATE DEBUG)
    target_compile_options(Sandbox PRIVATE $<$<CONFIG:DEBUG>:-g>)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Sandbox PRIVATE NDEBUG)
    target_compile_options(Sandbox PRIVATE $<$<CONFIG:RELEASE>:-O3>)
endif()

# Define the source and destination for the Assets folder copy
set(ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR}/Sandbox/Assets)

# Add a custom command to copy the Assets folder after the Sandbox target is built
add_custom_command(
    TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_SOURCE_DIR} ${ASSETS_DEST_DIR}
    COMMENT "Copying Assets folder to build directory"
)

# Debugging information
message("ASSETS_SOURCE_DIR: ${ASSETS_SOURCE_DIR}")
message("ASSETS_DEST_DIR: ${ASSETS_DEST_DIR}")
