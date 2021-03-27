
#include <iostream>
#include "Game.h"
#include "MapDriver.h"
#include "MapLoaderMain.h"
#include "PlayerDriver.h"
#include "CardsMain.h"
#include "BidingFacilityMain.h"

using namespace std;

int main() {
    Game* game = new Game();

    if (!game->start()) {
        cout << "Game start failed!" << endl;
        return 0;
    }
    cout << "Game start phase completed! Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();

    if (!game->startup()) {
        cout << "Game startup failed!" << endl;
        return 0;
    }
    cout << "Game startup phase completed! Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();

    game->play();
    game->computeScore();
    game->claimWinner();

//    mapDriver::main();
//    mapLoader::main();
//    player::main();
//    cards::main();
//    biding::main();
}




