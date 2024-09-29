# 设置CMake的最小版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(BplusTree)

# 添加bplus_test作为一个可执行文件
add_executable(bplus_test bplus_test.cpp)