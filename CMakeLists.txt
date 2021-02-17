cmake_minimum_required(VERSION 3.17)
project(comp345_winter2021)

set(CMAKE_CXX_STANDARD 17)

add_executable(comp345_winter2021
        Cards.h
        Cards.cpp
        Map.h
        Map.cpp
        Player.h
        Player.cpp
        BidingFacility.h
        BidingFacility.cpp
        MapLoader.cpp
        MapLoader.h
        MapLoaderMain.cpp
        )
