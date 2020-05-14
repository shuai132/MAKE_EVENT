cmake_minimum_required(VERSION 3.1)

project(MakeEvent)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall)

add_executable(${PROJECT_NAME}_example example.cpp)
