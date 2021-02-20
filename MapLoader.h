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
    MapLoader( MapLoader * mapLoader);
    ~MapLoader();
    friend ostream& operator<<(ostream& output, MapLoader * mapLoader);
    MapLoader &operator=(const MapLoader &ml);
    Map * getGameMap();
    string getFile();
    bool getLshape();
    int getNumberofmapboard();
    int getNumberofregions();
    int getNumberofcontinents();
private:
    string file;
    bool lshape;
    Map * GameMap;
    string mapboard_order;
    int number_of_mapboard,number_of_regions,number_of_continents;
    void split(string,const string&, vector<string>&);
    void split(string,const string&, vector<int>&);
};

