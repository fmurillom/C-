cmake_minimum_required(VERSION 3.9)
project(mServer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-pthread")



add_executable(mServer cajun includes/memBlock.h source/memBlock.cpp main.cpp)