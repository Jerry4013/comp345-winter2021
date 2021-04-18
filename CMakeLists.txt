cmake_minimum_required(VERSION 3.8)
project(comp345_winter2021)

set(CMAKE_CXX_STANDARD 17)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
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
        PlayerDriver.h
        PlayerDriver.cpp
        MapLoaderMain.h
        MapLoaderMain.cpp
        BidingFacilityMain.h
        BidingFacilityMain.cpp
        CardsMain.h
        CardsMain.cpp
        MapDriver.h
        MapDriver.cpp
        GameEngine.cpp
        GameEngine.h
        MainDriver.cpp
        PlayerStrategies.cpp
        PlayerStrategies.h
        GameObservers.h
        GameObservers.cpp
        Observer.h
        Observer.cpp
        Subject.h
        Subject.cpp
        )
