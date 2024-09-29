cmake_minimum_required(VERSION 3.10) # 设置CMake最小版本要求
project(SkipList) # 设置项目名称

set(CMAKE_CXX_STANDARD 17) # 设置C++标准

add_executable(SkipList skiplist.cpp) # 添加可执行文件