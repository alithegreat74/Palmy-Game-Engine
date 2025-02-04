cmake_minimum_required(VERSION 3.20)

project(Palmy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /Zi /EHsc) 
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -g")
endif()

# Add subdirectories
add_subdirectory(${CMAKE_SOURCE_DIR}/Palmy)
add_subdirectory(${CMAKE_SOURCE_DIR}/Sandbox)
add_subdirectory(${CMAKE_SOURCE_DIR}/Thirdparty/glm)

# Set the startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

# Link Sandbox to the Engine library
target_link_libraries(Engine PRIVATE glm)
target_link_libraries(Sandbox PRIVATE Engine glm)

