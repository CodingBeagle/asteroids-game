cmake_minimum_required(VERSION 3.10)

# set the project name
project(helloworld)

# specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(helloworld helloworld.cpp)