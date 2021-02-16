//
// Created by Ming on 2/7/2021.
//

#pragma once

#include "BidingFacility.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class BidingFacility {
public:
    BidingFacility();

    BidingFacility(string pString[4], int i);

    void start();
    void getResultLog();
    void initialize();
    void initialize(string *_players, int _size);
private:
    string resultLog;
    bool ifInitialized = false;
    vector<string> players;
};