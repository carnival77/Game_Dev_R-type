find_package(Threads)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.h")

add_executable(r-type_client ${SOURCES} ${INCLUDES})

target_link_libraries (r-type_client Threads::Threads sfml-window sfml-system sfml-audio sfml-graphics)