cmake_minimum_required(VERSION 3.17)
project(Neon)

# Include directories
include_directories(vendor/spdlog/include)
include_directories(src)

# Add files
file(GLOB_RECURSE SOURCES src/**.h src/**.cpp)

# Create library
add_library(${PROJECT_NAME} STATIC ${SOURCES})
