find_package(Threads)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${CMAKE_INCLUDE_PATH})
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.h")

add_executable(r-type_server ${SOURCES} ${INCLUDES})

target_link_libraries (r-type_server rtype_common Threads::Threads) 