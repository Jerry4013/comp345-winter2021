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
    Territory();
    ~Territory();
    Territory(const Territory&);
    Territory(std::string TerritoryName,int TerritoryNumber,int ContinentNumber);
    Territory& operator=(const Territory& secondTerritory);
    friend ostream& operator<<(ostream& out, const Territory& territory);

    string getName() const;
    void setName(const string& newName);
    int getId() const;
    void setId(const int newId);
    int getContinentId() const;
    void setContinentId(const int newContinentId);

    int getArmiesOfPlayer(int playerId);
    void placeNewArmiesOfPlayer(int playerId, int numOfNewArmies);
    void removeArmiesOfPlayer(int playerId, int numOfArmiesToRemove);
    int displayCityInfo();
    void buildCity(int playerId);
    vector<int> getNeighbors();
    void addNeighbor(int neighborId, int distance);
    int getDistance(int neighborId);
    int getOwningPlayerId() const; // If this territory is not owned by anyone, return 0;

    string toString() const;
    void printTerritory();
private:
    int id;
    string name;
    int continentId;
    unordered_map<int, int> armies; // playerId -> number of armies
    unordered_map<int, bool> cities; // playerId -> whether this player has built city here
    vector<int> neighbors;          // neighbor Id list
    unordered_map<int, int> distance; // neighborId -> the distance to this neighbor (1 or 3).
};

class Continent{
public:
    ~Continent();
    Continent(int id, string name, vector<Territory*> territories, vector<int> neighbors);
    Continent(const Continent&);
    Continent& operator=(const Continent& continent);
    friend ostream& operator<<(ostream& out, const Continent& continent);

    int getId() const;
    void setId(int id);
    string getName() const;
    void setName(string name);
    void addTerritory(Territory* territory);
    void addNeighbor(int neighborContinentId);
    vector<int> getTerritoryIdList();
    Territory* getTerritoryById(int id) const;
    int getOwningPlayerId() const; // If this continent is not owned by anyone, return 0;
private:
    int id;
    string name;
    vector<Territory*> territories;
    vector<int> neighbors;
};


class Map {
public:
    Map(vector<Territory*> territories);
    Map(vector<Continent*> continents);
    Map(vector<Continent*> continents, vector<Territory*> territories);
    ~Map();
    Map(const Map&);
    Map& operator=(const Map& map);
    friend ostream& operator<<(ostream& out, const Map& map);

    Territory* getTerritoryById(int id);
    Continent* getContinentById(int id);
    bool validate();
    bool checkTerritoryBelongsToOneContinent(Map* map);
    void addEdgesTerritory(Territory *, Territory *);
    void printMap();
private:
    vector<Continent*> continents;
    vector<Territory*> territories;
    unordered_map<int, vector<int>> territoryAdjacencyList;  // territoryId -> list of it's neighbors id;
    unordered_map<int, vector<int>> continentAdjacencyList;  // continentId -> list of it's neighbors id;
    void dfsTerritories(vector<bool>& visited, int territoryId);
    bool validateTerritories();
    bool validateContinents();
};

