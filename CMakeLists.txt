cmake_minimum_required(VERSION 3.15)
project(comp345_winter2021)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(comp345_winter2021
        Map.cpp
        Map.h
        MapDriver.cpp)
