cmake_minimum_required(VERSION 3.17)
project(Sandbox)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Neon/src)
include_directories(${CMAKE_SOURCE_DIR}/Neon/vendor/spdlog/include)

# Add files
file(GLOB_RECURSE SOURCES src/**.h src/**.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)

# Add dependencies
add_dependencies(${PROJECT_NAME} Neon)

# Link dependencies
target_link_libraries(${PROJECT_NAME} Neon)
