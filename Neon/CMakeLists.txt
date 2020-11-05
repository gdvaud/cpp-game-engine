cmake_minimum_required(VERSION 3.17)
project(Neon)

# Vendor sub dirs
# GLFW
add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)

# Include directories
include_directories(vendor/spdlog/include)
include_directories(src)

# Add files
file(GLOB_RECURSE SOURCES src/**.h src/**.cpp)

# Create library
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_precompile_headers(${PROJECT_NAME} PRIVATE src/neon_pch.h)

# Vendor libs linking
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

