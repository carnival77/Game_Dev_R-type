project(Babel)
cmake_minimum_required(VERSION 3.5)
add_definitions("-fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
add_subdirectory(client)
add_subdirectory(server)
