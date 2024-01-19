cmake_minimum_required(VERSION 3.27)
project(renderer)

# set(SPIRV_DIRECTORY "spirv")
#
# if(NOT EXISTS ${SPIRV_DIRECTORY})
#     file(MAKE_DIRECTORY ${SPIRV_DIRECTORY})
# endif()
#
# set(SHADER_TIMESTAMP_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shader_timestamp")
#
# if(NOT EXISTS ${SHADER_TIMESTAMP_DIRECTORY})
#     file(MAKE_DIRECTORY ${SHADER_TIMESTAMP_DIRECTORY})
# endif()

set(RENDERER_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RENDERER_DIRECTORY})

file(GLOB_RECURSE src "src/*.c" "include/*.h")

add_library(renderer SHARED ${src})

target_include_directories(renderer PUBLIC "include/")
target_link_directories(renderer PUBLIC "lib/")
target_link_libraries(renderer PUBLIC "vulkan")

# file(GLOB_RECURSE shaders "shaders/*.vert" "shaders/*.frag")
#
# foreach(shader ${shaders})
#     string(REPLACE "${RENDERER_DIRECTORY}/shaders")
# endforeach()

if(DEFINED DEBUG)
    add_subdirectory("debug")
endif()
