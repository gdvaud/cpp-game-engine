cmake_minimum_required(VERSION 3.17)
project(Neon)


# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

# Include directories
include_directories(vendor/spdlog/include)
include_directories(vendor/glfw/include)
include_directories(src)

# Add files
file(GLOB_RECURSE SOURCES src/**.h src/**.cpp)

# Create library
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_precompile_headers(${PROJECT_NAME} PRIVATE src/neon_pch.h)

# Vendor libs linking
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

