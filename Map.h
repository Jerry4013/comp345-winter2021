//
// Created by Luojia yan on 2021-02-07.
//
#pragma once

#include <string>
#include <vector>
#include "map"
#include <unordered_map>

using namespace std;

class Territory {
public:
    ~Territory();
    Territory(const Territory&);
    Territory(int id, string& newName, int continentId);
    Territory& operator=(const Territory& secondTerritory);
    friend ostream& operator<<(ostream& out, const Territory& territory);

    int getId() const;
    void setId(int newId);
    string getName() const;
    void setName(const string& name);
    int getContinentId() const;
    void setContinentId(int newContinentId);

    int getArmiesOfPlayer(int playerId);
    void placeNewArmiesOfPlayer(int playerId, int numOfNewArmies);
    void removeArmiesOfPlayer(int playerId, int numOfArmiesToRemove);
    void displayCityInfo();
    void buildCity(int playerId);
    int getControllingPlayerId(); // If this territory is not owned by anyone, return 0;
    unordered_map<int, int>& getArmies();
    unordered_map<int, int>& getCities();
    void printTerritory();
    string toString() const;
private:
    int id;
    string name;
    int continentId;
    unordered_map<int, int> armies; // playerId -> number of armies
    unordered_map<int, int> cities; // playerId -> whether this player has built city here
};

class Continent{
public:
    Continent(int id, string& name);
    Continent(const Continent&);
    ~Continent();
    Continent& operator=(const Continent& continent);
    friend ostream& operator<<(ostream& out, const Continent& continent);

    int getId() const;
    void setId(int newId);
    string getName() const;
    void setName(string& newName);
    void addTerritory(Territory* territory);
    vector<int> getTerritoryIdList();
    Territory* getTerritoryById(int id) const;
    int getControllingPlayerId() const; // If this continent is not owned by anyone, return 0;
private:
    int id;
    int mapId;
    string name;
    vector<Territory*> territories;
};


class Map {
public:
    Map(int id, string& name);
    ~Map();
    Map(const Map&);
    Map& operator=(const Map& secondMap);
    friend ostream& operator<<(ostream& out, const Map& map);

    int getId() const;
    void setId(int newId);
    string getName() const;
    void setName(string& newName);
    vector<Continent*>& getContinents();
    void addContinent(Continent* newContinent);
    vector<Territory*>& getTerritories();
    Territory* getTerritoryById(int territoryId);
    Continent* getContinentById(int continentId);
    vector<int>&
    void addEdgesTerritory(int territoryId1, int territoryId2);
    void getTerritoryNeighborsById(int territoryId);
    void printTerritoryAdjacencyList();
    void printContinentAdjacencyList();
    bool validate();
    bool checkTerritoryBelongsToOneContinent(Map* map);
    Map* extend(Map* newMap);
private:
    int id;
    string name;
    vector<Continent*> continents;
    vector<Territory*> territories;
    unordered_map<int, vector<int>> territoryAdjacencyList;  // territoryId -> list of it's neighbors id;
    unordered_map<int, vector<int>> continentAdjacencyList;  // continentId -> list of it's neighbors id;
    void dfsTerritories(vector<bool>& visited, int territoryId);
    void dfsContinents(vector<bool>& visited, int continentId);
    bool validateTerritories();
    bool validateContinents();
};

