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

    // TODO: 以下六个方法，不需要暴露出来，函数内部实现就好了。
    Map * getGameMap();
    string getFile();
    bool getLshape();
    int getNumberofmapboard();
    int getNumberofregions();
    int getNumberofcontinents();

    // TODO：把原来的函数实现的功能放在以下这两个方法中。MapLoader属于工具类，函数都应该是static的
    static bool validateMapFile(string& filePath); // 只验证map文件的合法性，不需要验证地图的合法性
    static Map* loadMap(string& filePath); // 生成Map对象后，要使用Map里的validate方法，验证地图的合法性

    // TODO: 需要两个map文件，一个叫lshape.map,另一个叫rectangular.map
    // TODO: 建议直接使用json格式文件解析数据，不需要逐行读取txt文本。
private:

    // TODO: 以下属性均可删除，所有逻辑都放在两个static方法中。
    string file;
    bool lshape;
    Map * GameMap;
    string mapboard_order;
    int number_of_mapboard,number_of_regions,number_of_continents;
    void split(string,const string&, vector<string>&);
    void split(string,const string&, vector<int>&);
};

