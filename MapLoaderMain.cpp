//
// Created by Jingyi Lin on 2021-02-05.
//

#include <iostream>
#include "MapLoader.h"

using std::cout,std::endl;

int main(){
    MapLoader * mapLoader = new MapLoader("..\\GAME1.map");
    cout <<"hello"<<endl;
    //cout << *mapLoader << endl;
    return 0;
};