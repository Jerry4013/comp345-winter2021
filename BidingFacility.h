//
// Created by Ming on 2/7/2021.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

class BidingFacility {
public:
    BidingFacility();
    BidingFacility(const BidingFacility&);
    BidingFacility& operator=(const BidingFacility& secondBidingFacility);
    friend ostream& operator<<(ostream& out, const BidingFacility& bidingFacility);

    Player* bid(vector<Player*> players);
};