cmake_minimum_required(VERSION 3.10)
project(LRU)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "lru/*.cpp" "main.cpp")

add_executable(main ${SOURCES})