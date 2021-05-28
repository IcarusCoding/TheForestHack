cmake_minimum_required(VERSION 3.13)
project(TheForest_Hack_CLR)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES bootstrap.cpp)

add_executable(TheForest_Hack_CLR_Executable ${SOURCE_FILES})
add_library(TheForest_Hack_CLR_Shared SHARED ${SOURCE_FILES})