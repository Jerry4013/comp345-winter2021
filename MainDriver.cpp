
#include <iostream>

#include "Game.h"


using namespace std;

int main() {
    Game* game = new Game();
    bool gameStartSucceed = game->start();
    if (!gameStartSucceed) {
        cout << "Game start failed!" << endl;
        return 0;
    }
    game->startup();
    game->play();
    game->computeScore();
}




