#include <iostream>
#include <vector>
#include "Player.h"
#include <string>
#include "PlayerDriver.h"
#include "MapLoader.h"

using namespace std;

int player::main() {

    Map* map = MapLoader::loadMap("Maps/Rectangular.map");

    auto* player1 = new Player(1, "Jenny", "Smith", "white", 1, 18,
                               map->getTerritories(), new HumanStrategy());
    auto* player2 = new Player(1, "Ben", "Williams", "green", 1, 18,
                               map->getTerritories(), new HumanStrategy());
    cout << *player1 << endl;
    cout << *player2 << endl;
    vector<Player*> players;
    players.emplace_back(player1);
    players.emplace_back(player2);
    for (auto & player : players) {
        player->setPlayers(players);
        player->setTerritoryAdjacencyList(map->getTerritoryAdjacencyList());
    }
    Deck* deck = new Deck(2);
    Hand* hand = new Hand(deck);

    // PayCoin()
    cout << "Testing PayCoin(): " << endl;
    cout << "Player1 has coins " << player1->getCoins() << endl;
    player1->PayCoin(2);
    cout << "Now player1 has coins " << player1->getCoins() << endl;
    cout << endl;

    // PlaceNewArmies()
    cout << "Testing PlaceNewArmies(): " << endl;
    Territory* territory = map->getTerritories()[0];
    cout << "Player1 has " << territory->getArmiesOfPlayer(player1->getId()) << " armies at territory "
        << territory->getId() << endl;
    player1->PlaceNewArmies(5, territory);
    cout << "Now, player1 has " << territory->getArmiesOfPlayer(player1->getId()) << " armies at territory "
         << territory->getId() << endl;
    cout << endl;

    // MoveArmies()
    cout << "Testing MoveArmies(): " << endl;
    vector<int> neighbors = map->getTerritoryNeighborsById(territory->getId());
    Territory* to = map->getTerritoryById(neighbors[0]);
    player1->MoveArmies(1, territory, to, 5);
    cout << "Now, player1 has " << territory->getArmiesOfPlayer(player1->getId()) << " armies at territory "
         << territory->getId() << endl;
    cout << "Now, player1 has " << to->getArmiesOfPlayer(player1->getId()) << " armies at territory "
         << to->getId() << endl;
    cout << endl;

    // MoveOverLand()
    cout << "Testing MoveOverLand(): " << endl;
    cout << "Assume that player 1 has 5 moving points, and moving 2 armies overland." << endl;
    int remainingPoints = player1->MoveOverLand(2, 5);
    cout << "Now, player 1 has " << remainingPoints << " moving points." << endl;
    cout << endl;

    // MoveOverWater()
    cout << "Testing MoveOverWater(): " << endl;
    cout << "Assume that player 1 has 5 moving points, and moving 1 armies over water." << endl;
    remainingPoints = player1->MoveOverWater(1, 5);
    cout << "Now, player 1 has " << remainingPoints << " moving points." << endl;
    cout << endl;

    // BuildCity()
    cout << "Testing BuildCity(): " << endl;
    cout << "Player1 has " << territory->getCities()[player1->getId()] << " city at territory "
         << territory->getId() << endl;
    cout << "Player1 is building a city..." << endl;
    player1->BuildCity(territory, 1);
    cout << "Now, player1 has " << territory->getCities()[player1->getId()] << " city at territory "
         << territory->getId() << endl;
    cout << endl;

    // DestroyArmy()
    cout << "Testing DestroyArmy(): " << endl;
    cout << "Player1 has " << territory->getArmiesOfPlayer(player1->getId()) << " armies at territory "
         << territory->getId() << endl;
    cout << "Player2 is destroying an army of player1 at territory " << territory->getId() << endl;
    player2->DestroyArmy(1, player1, territory, 1);
    cout << "Now, player1 has " << territory->getArmiesOfPlayer(player1->getId()) << " armies at territory "
         << territory->getId() << endl;
    cout << endl;

    // AndOrAction()
    cout << "Testing AndOrAction(): " << endl;
    for (int i = 0; i < deck->getCards().size(); ++i) {
        if (deck->getCards()[i]->getAnd()) {
            cout << *deck->getCards()[i] << endl;
            player1->AndOrAction(deck->getCards()[i]);
            break;
        }
    }
    cout << endl;
    for (int i = 0; i < deck->getCards().size(); ++i) {
        if (deck->getCards()[i]->getOr()) {
            cout << *deck->getCards()[i] << endl;
            player1->AndOrAction(deck->getCards()[i]);
            break;
        }
    }

    return 0;
}

