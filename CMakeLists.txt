# CMake configuration based on https://github.com/pablospe/cmake-example-library

cmake_minimum_required(VERSION 2.6)

# Project name
project (scg3)
set(LIBRARY_NAME scg3)
set(LIBRARY_FOLDER scg3)

# Use C++ 11
set(CMAKE_CXX_STANDARD 11)

# Set variables
include(${CMAKE_SOURCE_DIR}/cmake/SetEnv.cmake)

# Check for required packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(X11 REQUIRED)
find_package(glfw3 REQUIRED)

# Libraries
set(LIBS ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${X11_LIBRARIES} ${GLUT_LIBRARY} glfw Xrandr Xxf86vm)

# Library sources
add_subdirectory (scg3)

# Example
add_subdirectory (scg3_example)

# Install targets
include(${CMAKE_SOURCE_DIR}/cmake/InstallConfig.cmake)
