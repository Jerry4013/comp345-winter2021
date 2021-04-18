//
// Created by Jingchao Zhang on 2/26/2021.
//

#ifndef COMP345_WINTER2021_GAMEENGINE_H
#define COMP345_WINTER2021_GAMEENGINE_H
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include <vector>
#include <string>
#include "Subject.h"

class GameEngine : public Subject {
public:
    GameEngine();
    ~GameEngine();
    bool start();
    bool startup();
    void play();
    void computeScore();
    void claimWinner();
    Player* getCurrentPlayer();
    int getCardIndex();
    Map* getMap();
    int getNumOfPlayers();
    bool isGameEnd();

private:
    int numOfPlayer;
    Map* map;
    vector<Player*> players;
    Deck* deck;
    Hand* hand;
    int coinSupply;
    int startRegionId;
    unordered_map<string, int> armies; // color -> the number of armies supplied on the table
    unordered_map<string, int> cities; // color -> the number of cities supplied on the table
    vector<string> COLORS;
    vector<int> order;   // [2, 3, 1] means player with id 2 move first, then player with id 3, then id 1;
    Player* currentPlayer;
    int cardIndex;
    bool gameEnd;
    int maxRound;
    bool tournamentMode;

    void selectMode();
    void createPlayers();
    bool selectMap();
    void selectNumberOfPlayers();
    void createDeck();
    void createArmiesAndCities();
    bool selectStartingRegion();
    void bidAndDecideMovingOrder();
    Player* getPlayerById(int id);
    bool criteriaA(int regionId);
    bool criteriaB(int regionId);
    void computeMapScore();
    void computeAbilityScore();
    void computeElixirScore();
    void displayWinner(Player* player);
    void printComponents();
    PlayerStrategy* selectStrategy();
    int selectBidding(int playerId, int coins);
    int initCoinsForEachPlayer();
    string selectColor(int playerId, vector<string> remainingColors);
    void changeStrategyPrompt(Player* currentPlayer);
};


#endif //COMP345_WINTER2021_GAMEENGINE_H