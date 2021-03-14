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
        mapLoader = new MapLoader();
        [[maybe_unused]] Map *mapptr = mapLoader->loadMap("..\\Maps\\GAME1.map");
        mapptr->printContinentAdjacencyList();
        mapptr->printTerritoryAdjacencyList();
        mapptr->validate();
        //mapLoader->getGameMap()->PrintContinentMatrix();
        //mapLoader->getGameMap()->PrintTerritoryMatrix();
        //mapLoader->getGameMap()->validate(mapLoader->getGameMap());

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