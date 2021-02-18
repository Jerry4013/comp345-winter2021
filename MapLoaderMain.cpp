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
    mapLoader_valid= nullptr;
    delete mapLoader,mapLoader_invalid,mapLoader_valid;

    return 0;
};