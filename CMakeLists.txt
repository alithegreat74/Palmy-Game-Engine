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

add_subdirectory(${CMAKE_SOURCE_DIR}/Palmy)
add_subdirectory(${CMAKE_SOURCE_DIR}/Sandbox)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

target_link_libraries(Sandbox PRIVATE Engine)
