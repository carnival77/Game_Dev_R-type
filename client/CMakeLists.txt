find_package(Threads)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${CMAKE_INCLUDE_PATH})
include_directories(include)
include_directories(${Boost_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")
file(GLOB INCLUDES "include/*.h")

#add_executable(r-type_client ${SOURCES} ${INCLUDES})
add_executable(client
    client.cpp
)

#target_link_libraries (r-type_client Threads::Threads sfml-window sfml-system sfml-audio sfml-graphics)
target_link_libraries(client
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)