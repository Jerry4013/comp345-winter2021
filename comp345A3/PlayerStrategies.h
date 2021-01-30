//
// Created by Luojia yan on 2020-12-02.
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Player.h";
class Player;
class PlayerStrategies{
public:
    PlayerStrategies();
    string PlayerStatus;
};
class HumanPlayerStraregies:PlayerStrategies{

    void SetPlayerStatus(Player* player);
    string GetPlayerStatus(Player* player);

};

class BenevolentPlayerStraregies:PlayerStrategies{
    //weakest contry
    //move to weakest
    void SetPlayerStatus(Player* player);
    string GetPlayerStatus(Player* player);
};
class AggressivePlayerStraregies:PlayerStrategies{
    //strongest contry
    //attack until can't
    //move armies to boarder
    void SetPlayerStatus(Player* player);
    string GetPlayerStatus(Player* player);
};
class NeutralPlayerStraregies:PlayerStrategies{
    //do nothing
    void SetPlayerStatus(Player* player);
    string GetPlayerStatus(Player* player);
};