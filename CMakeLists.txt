# I set the minimum required version of CMake to be used for this project.
# Using any CMake version lower than this will result in an error.
cmake_minimum_required(VERSION 3.10)

# Sets the name of the project.
# This name will be stored in a variable called PROJECT_NAME.
# Called from the top-level CMakeLists.txt will also store it in the variable CMAKE_PROJECT_NAME.
project(asteroidsgame)

# Add GLFW header files to search path for build
include_directories("dependencies/GLFW/include")

# Add project include folder as place to search for header files
include_directories("include")

# I use find_library to find the full path to a static library file.
# From the documentation this is the preferred way to find a path to a library.
# The result is stored in the "GLFW" variable.
# HINTS can be uesd to specify paths to search for the library.
find_library(GLFW glfw3dll-debug-x64 HINTS "dependencies/glfw")

# The add_executable command is used to produce an executable based on a list of source files.
# The first argument, the name, will be the name used for the produced executable.
add_executable(asteroidsgame src/main.cpp src/glad.c src/filehelper.cpp)

# I use target_link_libraries to specify a library that should be linked to a specific target.
target_link_libraries(asteroidsgame ${GLFW})

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