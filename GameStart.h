//
// Created by jingyi on 3/5/2021.
//

#ifndef COMP345_WINTER2021_GAMESTART_H
#define COMP345_WINTER2021_GAMESTART_H
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include <vector>
#include <iostream>
#include <filesystem>


class GameStart {
public:
    GameStart();
    GameStart(int numOfPlayer);
    ~GameStart();
    static void start();

private:
    int numOfPlayer;
    Map* map;
    vector<Player*> players;
    Deck* deck;
    Hand* hand;
    int coins;
    int nonPlayerArmy;
    int turn;   // if two players, then turn could be 1 or 2.
};


#endif //COMP345_WINTER2021_GAME_H
