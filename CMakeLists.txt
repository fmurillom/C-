cmake_minimum_required(VERSION 3.9)
project(mServer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-pthread")

set(CMAKE_C_COMPILER /usr/bin/gcc-7)

set(CMAKE_CXX_COMPILER /usr/bin/g++-7)



add_executable(Proyecto_1_v0 includes/cajun includes/memBlock.h source/memBlock.cpp sintaxys/mainS.cpp includes/S_List.h includes/Scoope.h source/Scoope.cpp mManager/main.cpp)
