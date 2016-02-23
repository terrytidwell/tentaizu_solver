cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Tentaizu_Solver)
enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -std=c++1y")
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/board_files)

add_subdirectory(tests)
