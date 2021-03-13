//
// Created by lllll on 2021-03-13.
//

#ifndef COMP345_WINTER2021_GAMESTART_H
#define COMP345_WINTER2021_GAMESTART_H

#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "MapLoader.h"
#include <iostream>
#include <filesystem>
#include <vector>
using std::string;

class GameStart {
public:
    GameStart();
    GameStart(int numOfPlayer, Map* gameMap);
    ~GameStart();
    void start();
    void startup();
    void play();
    void computeScore();

private:
    int numOfPlayer;
    Map* map;
    vector<Player*> players;
    Deck* deck;
    Hand* hand;
    int coinSupply;
    int nonPlayerArmy;
    int turn;   // if two players, then turn could be 1 or 2.
    void createPlayers();
};


#endif //COMP345_WINTER2021_GAMESTART_H
