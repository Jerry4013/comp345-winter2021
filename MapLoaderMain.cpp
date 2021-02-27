//
// Created by Jingyi Lin on 2021-02-05.
//

#include <iostream>
#include "MapLoader.h"
#include "MapLoaderMain.h"

using std::cout,std::endl;

int mapLoader::main() {
    MapLoader *mapLoader,*mapLoader_invalid, *mapLoader_valid, *mapLoader_copy;
    try {
        cout << "Loading valid map"<<endl;
        mapLoader = new MapLoader("..\\GAME1.map");
        cout << mapLoader <<endl;

        mapLoader_valid = mapLoader;
        cout << "Used assign operator"<<endl;
        cout << mapLoader_valid<<endl;

        mapLoader_copy = new MapLoader(mapLoader);
        cout<< "Used copy constructor"<<endl;
        cout << mapLoader_copy <<endl;
        //mapLoader->getGameMap()->PrintContinentMatrix();
        //mapLoader->getGameMap()->PrintTerritoryMatrix();
        mapLoader->getGameMap()->validate(mapLoader->getGameMap());

        cout<<endl;
        cout <<"Loading invalid map"<<endl;
        mapLoader_invalid = new MapLoader("..\\GAME1_invalid.map");
        cout << mapLoader_invalid <<endl;


    }
    catch (const std::string e) {
        cout << e<<endl;
    }

    delete mapLoader,mapLoader_invalid,mapLoader_valid,mapLoader_copy;
    mapLoader= nullptr;
    mapLoader_invalid= nullptr;
    mapLoader_valid= nullptr;
    mapLoader_copy = nullptr;

    return 0;
};