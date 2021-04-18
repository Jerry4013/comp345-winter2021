//#define _DEBUG
//
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//
//#endif

#include <iostream>
#include "Game.h"
#include "GameObservers.h"

using namespace std;

int main() {
//#ifdef _DEBUG
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
    Game* game = new Game();
    PhaseObserver* phaseObserver = new PhaseObserver(game);
    StatisticsObserver* statisticsObserver = new StatisticsObserver(game);

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

    delete phaseObserver;
    delete statisticsObserver;
    delete game;
}




