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
    MapLoader(MapLoader* mapLoader);
    ~MapLoader();
    friend ostream& operator<<(ostream& output, MapLoader * mapLoader);
    MapLoader &operator=(const MapLoader &ml);

    static Map* loadMap(string filePath);
    static int counter;
    static string lshape;
private:
    static void validateMapFile(vector<string>,vector<string>,vector<string>,int, int,int);
    static void split(string,const string&, vector<string>&);
    static void split(string,const string&, vector<int>&);
    void validateMapFile(vector<string> map_buffer, vector<string> continent_buffer, vector<string> regions_buffer);
};

