//
// Created by Luojia yan on 2021-02-07.
//
#pragma once

#include <string>
#include <vector>
#include <list>
#include <queue>
#include "map"
#include <unordered_map>

using namespace std;


class Territory {
private:
    std::string TerritoryName;
    int TerritoryNumber;
    //TODO::
    int ContinentNumber;
    int PlayerArmyArray[3];
    std::map<string,int> territoryArmies;
    std::map<string,int> territoryCities;
public:
    Territory();
    ~Territory();
    Territory(std::string TerritoryName,int TerritoryNumber,int ContinentNumber);
    friend ostream& operator<<(ostream& out, const Territory& territory);
    std::string GetTerritoryName();
    std::string GetPlayerName();
    int GetTerritoryNumber();
    int GetContinentNumber();
    int GetNumTroops(string PlayerNumber);
    void SetNumTroops(string PlayerNum,int num);
    int getCities(const string& playerName);
    void setCities(const string& playerName, int number);
    string toString() const;
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
    int GetContinentNum();
};


class Map {
private:
    std::string MapName;
    std::vector<Continent*> continents;
    //consider using hashmap
    //TODO::Made change
    std::unordered_map<int,Continent*> continent_hashmap;
    vector<vector<int> > continentMatrix;
    vector<vector<int> > territoryMatrix;
    void dfs(unordered_map<int, vector<int>>& neighborsMap, vector<bool>& visited, int territoryNumber);
public:
    Map(std::string mapName, int numberOfContinents, int numberOfRegions);
    ~Map();
    std::string GetMapName();

    std::vector<Continent*> ReturnContient();

    std::unordered_map<int,Continent*> ReturnContinentHashMap();
    void AddContinent(Continent* continent);

    void traverseTerritory(int u, bool visited[]);
    void traverseContinent(int u, bool visited[]);

    void Validate(Map* map);
    bool CheckTerritoryBelongToOneContinent(Map* map);
    bool validateTerritory();
    bool validateContinent();
    vector<vector<int> >& getContinentMatrix();
    vector<vector<int> >& getTerritoryMatrix();
    //TODO::Made change
    void AddEdgesCountry(Territory *,Territory *);
    void DeleteEdgesCountry(int TerritoryOne,int TerritoryTwo);

    //TODO::Delete addedgescontinents
    void AddEdgesContinents(int ContinentOne,int ContinentTwo);
    void DeleteEdgesContinents(int ContinentOne,int ContinentTwo);
    void PrintTerritoryMatrix();
    void PrintContinentMatrix();
    bool dfsValidate();
};

