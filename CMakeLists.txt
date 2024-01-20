#[[ if(NOT DEFINED GLSL_COMPILER)
    set(GLSL_COMPILER "glslc")
endif() ]]

cmake_minimum_required(VERSION 3.27)
project(renderer)

set(RENDERER_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RENDERER_DIRECTORY})

#[[ file(GLOB_RECURSE shaders "shaders/*.vert" "shaders/*.frag")

foreach(shader_file_path ${shaders})
    string(REPLACE "${RENDERER_DIRECTORY}/shaders" "" shader_relative_directory ${shader_file_path})

    add_custom_command(
        OUTPUT "${shader_file_path}.spv"
        PRE_BUILD
        COMMAND ${GLSL_COMPILER} -o ${shader_file_path}.spv ${shader_file_path}
        WORKING_DIRECTORY ${RENDERER_DIRECTORY}
    )

    list(APPEND spirv "${shader_file_path}.spv")
endforeach()

add_custom_target(
    spirv_target ALL
    DEPENDS ${spirv}
)

file(GLOB_RECURSE test "shaders/*.spv")
message("${test} !") ]]

file(GLOB_RECURSE src "src/*.c" "include/*.h" "shaders/*.c")

add_library(renderer SHARED ${src})

# add_dependencies(renderer spirv_target)

target_include_directories(renderer PUBLIC "include/")
target_link_directories(renderer PUBLIC "lib/")
target_link_libraries(renderer PUBLIC "vulkan")

if(DEFINED DEBUG)
    add_subdirectory("debug")
endif()
