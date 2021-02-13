//
// Created by Jingyi Lin on 2021-02-05.
//

#include <iostream>
#include "MapLoader.h"

using std::cout,std::endl;

int main(){
    string a="";
    cout << a.empty()<<endl;
    try {
        MapLoader * mapLoader = new MapLoader("..\\GAME1.map");
    }
    catch (const std::string e) {
        cout << e<<endl;
    }

    //cout << *mapLoader << endl;


    return 0;
};