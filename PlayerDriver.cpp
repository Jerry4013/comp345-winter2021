#include <iostream>
#include <vector>
#include "Player.h"
#include <string>
#include "PlayerDriver.h"
#include "MapLoader.h"

using namespace std;

int player::main() {

    Map* map = MapLoader::loadMap("../Maps/Rectangular.map");

    auto* player1 = new Player(1, "Jenny", "Smith", "white", 1, 18,
                               map->getTerritories());
    auto* player2 = new Player(1, "Ben", "Williams", "green", 1, 18,
                               map->getTerritories());
    cout << *player1 << endl;
    cout << *player2 << endl;
    // TODO 测试各种方法

    return 0;
}

