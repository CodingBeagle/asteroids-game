# CMake - Basic Overview

Controlling the build process with CMake is done through CMakeLists.txt files in directories within a project.

CMakeLists.txt files contains commands, executed in the order that they are listed by CMake.

## Targets

A "target" in CMake typically either corresponds to an executable or a library. In CMake, you can then express the dependencies between targets, in order for CMake to determine the build order and regeneration rules in response to changes.