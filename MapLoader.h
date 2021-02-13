//
// Created by lllll on 2021-02-05.
//
#pragma once
#include <iostream>
#include <string>
#include "Map.h"

using namespace std;

class MapLoader {

public:
    MapLoader();
    MapLoader(string);
    MapLoader(const MapLoader &ml);
    friend ostream& operator<<(ostream& output, const MapLoader& mapLoader);
    Map * getGameMap();
    string getFile();
private:
    string file;
    Map * GameMap;
    void makingconnection();

};

