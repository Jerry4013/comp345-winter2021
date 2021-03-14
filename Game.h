//
// Created by jerry on 2/26/2021.
//

#ifndef COMP345_WINTER2021_GAME_H
#define COMP345_WINTER2021_GAME_H
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include <vector>
#include <string>

class Game {
public:
    Game();
    ~Game();
    bool start();
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
    unordered_map<string, int> armies; // color -> the number of armies supplied on the table
    unordered_map<string, int> cities; // color -> the number of cities supplied on the table
    static const vector<int> CARD_COSTS;
    static const vector<string> COLORS;
    vector<int> order;   // [2, 3, 1] means player with id 2 move first, then player with id 3, then id 1;
    void createPlayers();
    bool selectMap();
    void selectNumberOfPlayers();
    void createDeck();
    void createArmiesAndCities();
    void printSixCards();
    int selectStartingRegion();
    void bid();
};


#endif //COMP345_WINTER2021_GAME_H