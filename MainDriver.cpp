
#include <iostream>

#include "Game.h"


int main(){
    Game* game = new Game(2);
    game->start();
    game->startup();
    game->play();
    game->computeScore();
}


