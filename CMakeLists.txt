cmake_minimum_required(VERSION 3.6)
project(BBTree)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES BBTree.h BBTree.cpp main.cpp)
add_executable(BBTree ${SOURCE_FILES})