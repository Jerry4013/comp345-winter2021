//
// Created by jerry on 2/26/2021.
//

#ifndef COMP345_WINTER2021_GAME_H
#define COMP345_WINTER2021_GAME_H
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include <vector>

class Game {
public:
    Game();
    Game(int numOfPlayer, Map* gameMap);
    ~Game();
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


#endif //COMP345_WINTER2021_GAME_H