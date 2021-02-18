//
// Created by Ming on 2/15/2021.
//
#include "BidingFacilityMain.h"
#include "BidingFacility.h"
using namespace std;

int biding::main (){
    cout << "\nTesting Driver >> Biding Facility" << endl;

    // {"Jack","Tim", "July", "Thierry"} {"Ngyuan", "Noah", "Chen"}
    string players[3]  = {"Ngyuan", "Noah", "Chen"};
    int size = sizeof(players)/sizeof(players[0]);

    BidingFacility bf;
    bf.initialize(players, size);
    bf.start();
    bf.getResultLog();

    return 0;
}