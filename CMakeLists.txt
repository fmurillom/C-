cmake_minimum_required(VERSION 3.9)
project(mServer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-pthread")



add_executable(Proyecto_1_v0 includes/cajun includes/memBlock.h source/memBlock.cpp sintaxys/mainS.cpp includes/S_List.h includes/Scoope.h source/Scoope.cpp main.cpp)
