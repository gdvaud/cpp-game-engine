cmake_minimum_required(VERSION 3.17)
project(Sandbox)

file(GLOB_RECURSE SOURCES src/**.h src/**.cpp)

include_directories(${CMAKE_SOURCE_DIR}/Neon/src)

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} Neon)

target_link_libraries(${PROJECT_NAME} Neon)
