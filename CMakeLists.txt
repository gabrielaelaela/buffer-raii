cmake_minimum_required(VERSION 3.10)
project(Buffer LANGUAGES CXX)

add_executable(Buffer main.cpp)
add_library(buffer STATIC buffer.cpp)
add_library(buffer_view STATIC buffer_view.cpp)

target_link_libraries(Buffer PUBLIC buffer)
target_link_libraries(Buffer PUBLIC buffer_view)

