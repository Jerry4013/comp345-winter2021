#include "BidingFacility.h"
#include <iostream>
#include <vector>

using namespace std;


int BidingFacility::bid(vector<Player *>& players) {
    int bidding;
    int highestBidding = -1;
    vector<Player*> highestPlayers;
    for (int i = 0; i < players.size(); ++i) {
        bidding = players[i]->getBiding();
        if (bidding > highestBidding) {
            highestBidding = bidding;
            highestPlayers.clear();
            highestPlayers.emplace_back(players[i]);
        } else if (bidding == highestBidding) {
            highestPlayers.emplace_back(players[i]);
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