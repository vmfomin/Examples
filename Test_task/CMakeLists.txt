cmake_minimum_required(VERSION 3.17)
project(Test_task)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS "header/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(Test_task main.cpp ${HEADERS} ${SOURCES})