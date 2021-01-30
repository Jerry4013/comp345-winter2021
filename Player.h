// PLAYER_H
#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Map.h"
//#include "card.h"
#include "OrderList.h"
#include <vector>
#include "card.h"
using namespace std;

class Order;
class OrdersList;
class Player {

private:
    std::string playerName;
    int reinforcementPool;
    Hand playerHand;
    int ownedTerritoriesCount;

//    Hand getHand();
public:
    Player();
    Player(string playerName);
    Player(string playerName, Hand hand);
    std::vector<Territory*> playerTerritory;
    OrdersList* player_ordersList;
    std::string getPlayerName();
    void setPlayerName(std::string playerName);
    std::vector<Territory*> DefendList;
    std::vector<Territory*> AttackList;
    void toDefend(Territory* territory);
    void toAttack(Territory* territory);
    int getReinforcementPool();
    void addArmiesToReinforcementPool(int numOfArmies);
    void setReinforcementPool(int numOfArmies);
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);
    int TakeArmiesFromReinforcementPool(int numOfArmies);
    int getOwnedTerritories();
    Hand& getHand();
    void issueOrder(vector<Territory> TerritoryList,int ConnectionBufferFromMap[100][100]);
    vector<Order*> getOrdersList();
};

#endif
