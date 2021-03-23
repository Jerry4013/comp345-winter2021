#include "BidingFacility.h"
#include <iostream>
#include <vector>

using namespace std;


int BidingFacility::bid(vector<Player *>& players) {
    int highestBidding = -1;
    vector<Player*> highestPlayers;
    for (auto & player : players) {
        int bidding = player->getBiding();
        if (bidding > highestBidding) {
            highestBidding = bidding;
            highestPlayers.clear();
            highestPlayers.emplace_back(player);
        } else if (bidding == highestBidding) {
            highestPlayers.emplace_back(player);
        }
    }
    if (highestPlayers.size() == 1) {
        return highestPlayers[0]->getId();
    }
    vector<Player*> alphabeticalLastNamePlayers;
    alphabeticalLastNamePlayers.emplace_back(highestPlayers[0]);
    string lastName = highestPlayers[0]->getLastName();
    for (int i = 1; i < highestPlayers.size(); ++i) {
        if (highestPlayers[i]->getLastName() < lastName) {
            lastName = highestPlayers[i]->getLastName();
            alphabeticalLastNamePlayers.clear();
            alphabeticalLastNamePlayers.emplace_back(highestPlayers[i]);
        } else if (highestPlayers[i]->getLastName() == lastName) {
            alphabeticalLastNamePlayers.emplace_back(highestPlayers[i]);
        }
    }
    if (alphabeticalLastNamePlayers.size() == 1) {
        return alphabeticalLastNamePlayers[0]->getId();
    }

    Player* winner = alphabeticalLastNamePlayers[0];
    string firstName = alphabeticalLastNamePlayers[0]->getFirstName();
    for (int i = 1; i < alphabeticalLastNamePlayers.size(); ++i) {
        if (alphabeticalLastNamePlayers[i]->getFirstName() < firstName) {
            winner = alphabeticalLastNamePlayers[i];
        }
    }
    return winner->getId();
}

BidingFacility::BidingFacility() {
    // BidingFacility has no member variable.
}

BidingFacility::BidingFacility(const BidingFacility &) {
    // BidingFacility has no member variable.
}

BidingFacility &BidingFacility::operator=(const BidingFacility &secondBidingFacility) = default;

ostream &operator<<(ostream &out, const BidingFacility &bidingFacility) {
    // BidingFacility has no member variable.
    return out;
}
