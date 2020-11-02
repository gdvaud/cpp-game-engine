cmake_minimum_required(VERSION 3.17)
project(Neon)

file(GLOB_RECURSE SOURCES src/**.h src/**.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
