# Set the project name
project (rtype_common)

file(GLOB SOURCES "src/*.cpp")

# Add a library with the above sources
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
