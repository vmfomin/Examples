cmake_minimum_required(VERSION 3.17)
project(Battlships_game)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADERS "src/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(Battlships_game main.cpp ${HEADERS} ${SOURCES})