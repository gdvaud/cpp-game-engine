cmake_minimum_required(VERSION 3.17)
project(Neon)

# Glad
add_subdirectory(vendor/glad)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

# Imgui
add_subdirectory(vendor/imgui)

# Glm
add_subdirectory(vendor/glm)

# Include directories
include_directories(vendor/spdlog/include)
include_directories(vendor/glad/include)
include_directories(vendor/glfw/include)
include_directories(vendor/imgui)
include_directories(vendor/glm)
include_directories(src)

# Add files
file(GLOB_RECURSE SOURCES src/**.h src/**.cpp)

# Create library
add_library(${PROJECT_NAME} STATIC ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/neon_pch.h src/neon_windows_pch.h)

# Vendor libs linking
target_link_libraries(${PROJECT_NAME} PRIVATE Glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
