cmake_minimum_required(VERSION 3.27)
project(renderer)

set(RENDERER_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RENDERER_DIRECTORY})

file(GLOB_RECURSE src "src/*.c" "include/*.h")

add_library(renderer SHARED ${src})

target_include_directories(renderer PUBLIC "include/")
target_link_directories(renderer PUBLIC "lib/")
target_link_libraries(renderer PUBLIC "vulkan")

if(DEFINED DEBUG)
    add_subdirectory("debug")
endif()
