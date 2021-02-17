//
// Created by Jingyi Lin on 2021-02-05.
//

#include <iostream>
#include "MapLoader.h"

using std::cout,std::endl;

int main(){
    MapLoader *mapLoader,*mapLoader_invalid;
    try {
        cout << "Loading valid map"<<endl;
        mapLoader = new MapLoader("..\\GAME1.map");
        cout << mapLoader <<endl;
        HelperFunctionMap helper;
        helper.PrintContinentMatrix();
        helper.PrintTerritoryMatrix();
        mapLoader->getGameMap()->Validate(mapLoader->getGameMap());

        cout<<endl;
        cout <<"Loading invalid map"<<endl;
        mapLoader_invalid = new MapLoader("..\\GAME1_invalid.map");
        cout << mapLoader_invalid <<endl;
    }
    catch (const std::string e) {
        cout << e<<endl;
    }
    mapLoader= nullptr;
    mapLoader_invalid= nullptr;
    delete mapLoader,mapLoader_invalid;

    return 0;
};