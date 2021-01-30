//
// Created by Luojia yan on 2020-11-21.
//

#pragma once
//#ifndef PLAYER_H
//#define PLAYER_H
#include "Map.h"
#include "OrdersLists.h"
#include "Cards.h"
#include <vector>
#include "PlayerStrategies.h"
class Order;
class PlayerStrategies;
class Player{

public:

    int reinforcementPool;
    int ownedTerritoriesCount;
    string PlayerName;
    Hand playerHand;
    vector<Order*> player_ordersList;
    vector<Territory*> territoryList;
    PlayerStrategies* Playerstrategies;

    Player();
    ~Player();
    Player(string playerName,vector<Territory*> territoryList,PlayerStrategies* Playerstrategies);


    //getter
    int getReinforcementPool();
    int getOwnedTerritories();
    string getPlayerName();
    Hand getHand();
    vector<Order *> getOrdersList();
    vector<Territory *> getTerritoryList();

    //setter
    void setPlayerName(const string &playerName);
    void setTerritoryList(const vector<Territory *> &territoryList);
    void setReinforcementPool(int reinforcementPool);


    void addArmiesToReinforcementPool(int numOfArmies);
    int TakeArmiesFromReinforcementPool(int numOfArmies);

    void addTerritory(Territory *territory);
    void removeTerritory(Territory *territory);
    vector<Territory *> toAttack(vector<Territory *> Map);
    vector<Territory *> toDefend();

    void issueOrder();
    void setStrategies(string status);
};

//class Player{
//
//public:
//
//    int reinforcementPool;
//    int ownedTerritoriesCount;
//    string PlayerName;
//    Hand playerHand;
//    vector<Order*> player_ordersList;
//    vector<Territory*> territoryList;
//
//
//    Player();
//    ~Player();
//    Player(string playerName,vector<Territory*> territoryList);
//
//
//    //getter
//    int getReinforcementPool();
//    int getOwnedTerritories();
//    string getPlayerName();
//    Hand getHand();
//    vector<Order *> getOrdersList();
//    vector<Territory *> getTerritoryList();
//
//    //setter
//    void setPlayerName(const string &playerName);
//    void setTerritoryList(const vector<Territory *> &territoryList);
//    void setReinforcementPool(int reinforcementPool);
//
//
//    void addArmiesToReinforcementPool(int numOfArmies);
//    int TakeArmiesFromReinforcementPool(int numOfArmies);
//
//    void addTerritory(Territory *territory);
//    void removeTerritory(Territory *territory);
//    vector<Territory *> toAttack(vector<Territory *> Map);
//    vector<Territory *> toDefend();
//
//    void issueOrder(Order *o);
//
//};

//#endif
