cmake_minimum_required(VERSION 3.17)
project(Glad)

file(GLOB_RECURSE SOURCES include/**.h src/**.c)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)