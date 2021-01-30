//
// Created by Luojia yan on 2020-11-21.
//
#pragma once
#include "Map.h"
#include "MapLoader.h"
#include "Player.h"
extern vector<Player*> PlayerList;
extern vector<Continent*> ContinentList;
extern vector<Territory*> TerritoryList;
extern int Mapchoose;
extern int NumberOfPlayersGlobal;




class HelperFunction{
public:
    void ReturnStatsAboutTerritory(Territory* territory);
    int ReturnNumberOfContries();
    int ReturnNumberOfContinents();

};


class GameStart{
private:
    int MapNumberChoose;
    int NumberOfPlayers;
    bool checkinput;
    MapLoader* loadmap;
    Territory* TerritoryObject;
    string ObserverAnswer;
public:
    void ChooseMap();
    void ChooseNumberOfPlayers();
    void OptionObserver();
    void Validate();
};


class StartUp{
public:
    void StartUpPhase();
};

class GameLoop{
public:
    void ReinforcementPhase();
    void IssueOrderPhase();
    void OrdersExecutionPhase();
    void WinningConditionValidation();

};