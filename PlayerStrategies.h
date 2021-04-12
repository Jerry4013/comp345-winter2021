//
// Created by jerry on 4/3/2021.
//

#ifndef COMP345_WINTER2021_PLAYERSTRATEGIES_H
#define COMP345_WINTER2021_PLAYERSTRATEGIES_H
#include "Cards.h"
#include "Map.h"

class PlayerStrategy {
public:
    virtual int selectCard(Hand *hand, int coins) = 0;
    virtual string toString() = 0;
    virtual void takeAction(Action action, int id, vector<Territory*>& territories, int &remainingCubesRef,
                            map<int, vector<int>> territoryAdjacencyList, int flyAbility, int &remainingCity,
                            map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap) = 0;
    virtual int selectOrCard(Card *card) = 0;
};

class HumanStrategy : public PlayerStrategy {
public:
    int selectCard(Hand *hand, int coins) override; // return a card index 0-5
    string toString() override;
    void takeAction(Action action, int id, vector<Territory*>& territories, int &remainingCubesRef,
                    map<int, vector<int>> territoryAdjacencyList, int flyAbility, int &remainingCity,
                    map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap) override;
    int selectOrCard(Card *card) override;
private:
    static int placeNewArmiesPrompt(int id, int movingPoints, vector<Territory*>& territories, int &remainingCubesRef);
    static int moveArmiesPrompt(int id, int movingPoints, vector<Territory*>& territories,
                         map<int, vector<int>>& territoryAdjacencyList, int flyAbility);
    static int buildCityPrompt(int id, int movingPoints, vector<Territory *> &territories, int &remainingCity);
    static int destroyArmyPrompt(int destroyPoints, vector<Territory*>& territories,
                          map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap);

    static void printTerritoriesForNewArmies(int id, vector<Territory*>& territories);
    static Territory* getTerritoryById(int territoryId, vector<Territory*>& territories);
    static void PlaceNewArmies(int id, int numberOfNewArmies, Territory* territory, int &remainingCubesRef);
    static int buildCity(int id, Territory* territory, int buildPoints, int &remainingCity);
    static void printMyTerritoriesWithArmies(int id, vector<Territory*>& territories);
    static void printNeighborsOfTerritoriesWithArmies(int id, vector<Territory*>& territories,
                                               map<int, vector<int>>& territoryAdjacencyList);
    static int MoveArmies(int id, int numberOfArmies, Territory* from, Territory* to, int movingPoints, int flyAbility);
    // return remaining movingPoints. If the return value equals the parameter movingPoints, then this move failed.
    static int MoveOverLand(int numberOfArmies, int movingPoints);
    // return remaining movingPoints. If the return value equals the parameter movingPoints, then this move failed.
    static int MoveOverWater(int numberOfArmies, int movingPoints, int flyAbility);
    static int DestroyArmy(int otherPlayerId, int numberOfArmies, Territory* territory, map<int, int*>& remainingCubesMap,
                    int destroyPoints);
};

class GreedyComputerStrategy : public PlayerStrategy {
public:
    // return a card index 0-5. This method will choose the first card that building a city or destroying opponents.
    // If no card meets this requirement, it will select the first card, index 0.
    int selectCard(Hand *hand, int coins) override;
    string toString() override;
    void takeAction(Action action, int id, vector<Territory*>& territories, int &remainingCubesRef,
                    map<int, vector<int>> territoryAdjacencyList, int flyAbility, int &remainingCity,
                    map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap) override;
    int selectOrCard(Card *card) override;
};

class ModerateComputerStrategy : public PlayerStrategy {
public:
    int selectCard(Hand *hand, int coins) override; // return a card index 0-5
    string toString() override;
    void takeAction(Action action, int id, vector<Territory*>& territories, int &remainingCubesRef,
                    map<int, vector<int>> territoryAdjacencyList, int flyAbility, int &remainingCity,
                    map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap) override;
    int selectOrCard(Card *card) override;
};

#endif //COMP345_WINTER2021_PLAYERSTRATEGIES_H
