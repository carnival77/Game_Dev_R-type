find_package(Threads)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.h")

add_executable(r-type_server ${SOURCES} ${INCLUDES})

target_link_libraries (r-type_server ${CMAKE_THREAD_LIBS_INIT})