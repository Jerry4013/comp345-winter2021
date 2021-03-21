
#include <iostream>
#include "BidingFacilityMain.h"
#include "Game.h"


using namespace std;

int main() {
//    biding::main();
    Game* game = new Game();

    if (!game->start()) {
        cout << "Game start failed!" << endl;
        return 0;
    }

    if (!game->startup()) {
        cout << "Game startup failed!" << endl;
        return 0;
    }

    game->play();
    game->computeScore();
}




