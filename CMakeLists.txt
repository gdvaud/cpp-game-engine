cmake_minimum_required(VERSION 3.17)
project(Neon_Engine)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(
        DEBUG
)

add_subdirectory(Neon)
add_subdirectory(Sandbox)
