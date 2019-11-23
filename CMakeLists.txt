project(Babel)
cmake_minimum_required(VERSION 3.5)
add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)
add_subdirectory(client)
add_subdirectory(server)
