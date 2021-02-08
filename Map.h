//
// Created by Luojia yan on 2021-02-07.
//
#pragma once

#include <string>
#include <vector>
#include <list>
#include <queue>
#include "map"
using namespace std;

extern int RegionMatrix[10][10];
extern int ContinentMatrix[10][10];




class Territory {
private:
    std::string TerritoryName;
    int TerritoryNumber;
    std::string ContinentName;
    int PlayerArmyArray[3];
    std::map<string,int> territorystats;
    //    Player* player;
public:
    Territory();
    ~Territory();
    Territory(std::string TerritoryName,int TerritoryNumber,std::string Continent);
    std::string GetTerritoryName();
    std::string GetPlayerName();
    std::string GetContinentName();
    int GetTerritoryNumber();
    int GetNumTroops(string PlayerNumber);
    void SetNumTroops(string PlayerNum,int num);
};

class HelperFunctionMap{
public:
    void AddEdgesCountry(int TerritoryOne,int TerritoryTwo);
    void DeleteEdgesCountry(int TerritoryOne,int TerritoryTwo);

    void AddEdgesContinents(int ContinentOne,int ContinentTwo);
    void DeleteEdgesContinents(int ContinentOne,int ContinentTwo);
    void PrintTerritoryMatrix();
    void PrintContinentMatrix();
};

class Continent{
private:
    std::string Continetname;
    std::vector<Territory*> territories;
    int ContinentNum;
public:
    ~Continent();
    Continent(std::string name,int ContinentNum);
    std::string GetContinentName();
    void AddTerritory(Territory* territory);
    std::vector<Territory*> ReturnTerritory();
    void AddEdgeContinent(int FirstContinent,int SecondContinent);
    void RemoveEdgeContinent(int FirstContinent,int SecondContinent);
    int GetContinentNum();
};


class Map {
private:
    std::string MapName;
    std::vector<Continent*> continents;
public:
    Map(std::string mapname);
    ~Map();
    std::string GetMapName();

    void CreateContinentMatrix();
    void CreateCountryMatrix();

    std::vector<Continent*> ReturnContient();
    void AddContinent(Continent* continent);

    void traverseTerritory(int u, bool visited[]);
    void traverseContinent(int u, bool visited[]);

    void Validate(Map* map);
    bool CheckTerritoryBelongToOneContinent(Map* map);
    bool validateTerritory();
    bool validateContinent();

};

