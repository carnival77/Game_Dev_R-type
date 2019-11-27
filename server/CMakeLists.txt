find_package(Threads)
find_package(Boost REQUIRED system)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${CMAKE_INCLUDE_PATH})
include_directories(include)
include_directories(${Boost_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.h")

add_executable(server
    server.cpp
)

#target_link_libraries (r-type_server Threads::Threads)
target_link_libraries(server
    ${Boost_LIBRARIES}
)