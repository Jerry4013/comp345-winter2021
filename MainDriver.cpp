
#include <iostream>
#include "Game.h"


using namespace std;

int main() {
    Game* game = new Game();

    if (!game->start()) {
        cout << "Game start failed!" << endl;
        return 0;
    }
    cout << "Game start phase competed! Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();

    if (!game->startup()) {
        cout << "Game startup failed!" << endl;
        return 0;
    }

    game->play();
    game->computeScore();
    game->claimWinner();
}




