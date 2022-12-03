cmake_minimum_required(VERSION 3.21.1)
project(SubsetSumProblem)

set(CMAKE_CXX_STANDARD 17)

add_executable(SubsetSumProblem main.cpp tp_args.hpp searchMethods.cpp searchMethods.h Problem.h)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")