# I set the minimum required version of CMake to be used for this project.
# Using any CMake version lower than this will result in an error.
cmake_minimum_required(VERSION 3.10)

# CMake uses a policy mechanism to introduce potentially breaking changes, in order to maintain backwards compatibility.
# Each new behaviour introduced gets a policy identifier CMP***, and we can then set specific policies explicitly to what behaviour we want.
# Here, I set CMP0076, which means that all source files in target_sources will be replaced by absolute paths.
cmake_policy(SET CMP0076 NEW)

# Sets the name of the project.
# This name will be stored in a variable called PROJECT_NAME.
# Called from the top-level CMakeLists.txt will also store it in the variable CMAKE_PROJECT_NAME.
project(asteroidsgame)

# I use find_library to find the full path to a static library file.
# From the documentation this is the preferred way to find a path to a library.
# The result is stored in the "GLFW" variable.
# HINTS can be uesd to specify paths to search for the library.
find_library(GLFW glfw3dll-debug-x64 HINTS "dependencies/glfw")

find_library(FreeType freetype HINTS "dependencies/freetype")

find_library(FreeTypeGl freetype-gl-release HINTS "dependencies/freetype-gl")

# The add_executable command is used to produce an executable based on a list of source files.
# The first argument, the name, will be the name used for the produced executable.
add_executable(asteroidsgame)

set_property(TARGET asteroidsgame PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDll")

# Add source files to the target
target_sources(asteroidsgame
                PUBLIC
                src/main.cpp
                src/glad.c
                src/filehelper.cpp
                src/shader.cpp
                src/shaderprogram.cpp
                src/texture.cpp
                src/sprite.cpp
                src/renderer2d.cpp)

# Add GLFW header files to search path for build
target_include_directories(asteroidsgame PUBLIC "dependencies/GLFW/include")

# Add project include folder as place to search for header files
target_include_directories(asteroidsgame PUBLIC "include")

# I use target_link_libraries to specify a library that should be linked to a specific target.
target_link_libraries(asteroidsgame ${GLFW})

target_link_libraries(asteroidsgame ${FreeType})

target_link_libraries(asteroidsgame ${FreeTypeGl})

add_custom_command(
    TARGET asteroidsgame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROJECT_SOURCE_DIR}/dependencies/GLFW/glfw3.dll"
    $<TARGET_FILE_DIR:asteroidsgame>)

add_custom_command(
    TARGET asteroidsgame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/dat"
    "$<TARGET_FILE_DIR:asteroidsgame>/dat")

add_custom_command(
    TARGET asteroidsgame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROJECT_SOURCE_DIR}/dependencies/freetype/freetype.dll"
    $<TARGET_FILE_DIR:asteroidsgame>)