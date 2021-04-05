//
// Created by Ming on 2/15/2021.
//
#include "BidingFacilityMain.h"
#include "BidingFacility.h"
#include <vector>
using namespace std;


int biding::main () {
    cout << "\nTesting Biding Facility:" << endl;
    vector<Player*> players;
    vector<string> firstNames{"John", "Danny", "Alice"};
    vector<string> lastNames{"Smith", "Brown", "Miller"};
    const vector<string> COLORS{"purple", "white", "green"};
    players.reserve(3);
    vector<Territory *> territories;
    for (int i = 0; i < 3; ++i) {
        players.emplace_back(new Player(i + 1, firstNames[i], lastNames[i], COLORS[i], 0, 14,
                                        territories, new HumanStrategy()));
    }
    players[0]->setBidding(2);
    players[1]->setBidding(1);
    players[2]->setBidding(1);
    cout << "The winner is player " << BidingFacility::bid(players) << endl;

    players[0]->setBidding(1);
    players[1]->setBidding(0);
    players[2]->setBidding(1);
    cout << "The winner is player " << BidingFacility::bid(players) << endl;

    players[0]->setBidding(0);
    players[1]->setBidding(0);
    players[2]->setBidding(0);
    cout << "The winner is player " << BidingFacility::bid(players) << endl;

    players[0]->setBidding(0);
    players[1]->setBidding(0);
    players[2]->setBidding(0);
    players[2]->setLastName(lastNames[1]);
    cout << "The winner is player " << BidingFacility::bid(players) << endl;
    for (auto & player : players) {
        delete player;
        player = nullptr;
    }
    return 0;
}