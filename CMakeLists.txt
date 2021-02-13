cmake_minimum_required(VERSION 3.17)
project(comp345_winter2021)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(comp345_winter2021
        Cards.cpp
        Cards.h
#        CardsMain.cpp

        WholeGame.cpp
        WholeGame.h)
