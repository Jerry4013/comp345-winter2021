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
    string TerritoryName;
    int TerritoryNumber;
    //TODO::
    int ContinentNumber;
    int PlayerArmyArray[3];
    map<string,int> territoryArmies;
    map<string,int> territoryCities;
public:
    Territory();
    ~Territory();
    Territory(const Territory&);
    Territory(std::string TerritoryName,int TerritoryNumber,int ContinentNumber);
    Territory& operator=(const Territory& secondTerritory);
    friend ostream& operator<<(ostream& out, const Territory& territory);
    string GetTerritoryName();
    string GetPlayerName();
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
    string ContinentName;
    vector<Territory*> territories;
    int ContinentNum;
public:
    ~Continent();
    Continent(std::string name,int ContinentNum);
    Continent(const Continent&);
    Continent& operator=(const Continent& continent);
    friend ostream& operator<<(ostream& out, const Continent& continent);
    string GetContinentName();
    void AddTerritory(Territory* territory);
    vector<Territory*> ReturnTerritory();
    int GetContinentNum();
};


class Map {
private:
    string MapName;
    vector<Continent*> continents;
    //consider using hashmap
    //TODO::Made change
    unordered_map<int,Continent*> continent_hashmap;
    vector<vector<int> > continentMatrix;
    vector<vector<int> > territoryMatrix;
    void dfs(unordered_map<int, vector<int>>& neighborsMap, vector<bool>& visited, int territoryNumber);
public:
    Map(std::string mapName, int numberOfContinents, int numberOfRegions);
    ~Map();
    Map(const Map&);
    Map& operator=(const Map& map);
    friend ostream& operator<<(ostream& out, const Map& map);
    string GetMapName();

    vector<Continent*> ReturnContinent();

    unordered_map<int,Continent*> ReturnContinentHashMap();
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

