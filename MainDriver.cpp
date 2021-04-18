//#define _DEBUG
//
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#endif

#include <iostream>
#include "GameEngine.h"
#include "GameObservers.h"

using namespace std;

int main() {
//#ifdef _DEBUG
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
    GameEngine* game = new GameEngine();
    PhaseObserver* phaseObserver = new PhaseObserver(game);
    StatisticsObserver* statisticsObserver = new StatisticsObserver(game);

    if (!game->start()) {
        cout << "Game start failed!" << endl;
    } else {
        cout << "Game start phase completed! Press Enter to continue..." << endl;
        cin.ignore(10, '\n');
        cin.get();

        if (!game->startup()) {
            cout << "Game startup failed!" << endl;
        } else {
            cout << "Game startup phase completed! Press Enter to continue..." << endl;
            cin.ignore(10, '\n');
            cin.get();

            game->play();
        }
    }
    delete statisticsObserver;
    delete phaseObserver;
    delete game;
}




