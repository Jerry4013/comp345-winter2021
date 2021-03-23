//
// Created by Luojia yan on 2021-02-07.
//
#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>


using namespace std;

class Territory {
public:
    Territory(int id, string& newName, int continentId);
    ~Territory();
    Territory(const Territory&);
    Territory& operator=(const Territory& secondTerritory);
    friend ostream& operator<<(ostream& out, const Territory& territory);

    int getId() const;
    void setId(int newId);
    string getName() const;
    void setName(const string& name);
    int getContinentId() const;
    void setContinentId(int newContinentId);
    bool getIsStartingRegion() const;
    void setIsStartingRegion(bool);

    int getArmiesOfPlayer(int playerId);
    void placeNewArmiesOfPlayer(int playerId, int numOfNewArmies);
    void removeArmiesOfPlayer(int playerId, int numOfArmiesToRemove);
    void displayCityInfo();
    void buildCity(int playerId);
    int getControllingPlayerId(); // If this territory is not owned by anyone, return -1;
    map<int, int>& getArmies();
    map<int, int>& getCities();
    void printTerritory();
private:
    int id;
    string name;
    int continentId;
    bool isStartingRegion;
    map<int, int> armies; // playerId -> number of armies
    map<int, int> cities; // playerId -> whether this player has built city here
};


class Continent{
public:
    Continent(int id, string& name, int mapId);
    ~Continent();
    Continent(const Continent&);
    Continent& operator=(const Continent& continent);
    friend ostream& operator<<(ostream& out, const Continent& continent);

    int getId() const;
    void setId(int newId);
    string getName() const;
    void setName(string& newName);
    int getMapId() const;
    void setMapId(int newMapId);
    void addTerritory(Territory* territory);
    vector<int> getTerritoryIdList();
    void printContinent();
    Territory* getTerritoryById(int territoryId) const;
    int getControllingPlayerId() const; // If this continent is not owned by anyone, return -1;
    vector<Territory*> getTerritories();
private:
    int id;
    string name;
    int mapId;
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
    void addTerritory(Territory* newTerritory);
    Territory* getTerritoryById(int territoryId);
    Continent* getContinentById(int continentId);
    vector<int>& getTerritoryNeighborsById(int territoryId);
    vector<int>& getContinentNeighborsById(int continentId);
    bool edgeExists(int territoryId1, int territoryId2);
    void addTerritoryEdges(int territoryId1, int territoryId2);
    int getDistance(int territoryId1, int territoryId2); // return -1 if no edge between them.
    void printTerritoryAdjacencyList();
    void printContinentAdjacencyList();
    bool validate();
    bool checkTerritoryBelongsToOneContinent();
    void printForce(int numOfPlayers); // print all army and city information of each play in all territories;
    map<int, vector<int>> getTerritoryAdjacencyList();
private:
    int id;
    string name;
    vector<Territory*> territories;
    vector<Continent*> continents;
    map<int, vector<int>> territoryAdjacencyList;  // territoryId -> list of it's neighbors id;
    map<int, vector<int>> continentAdjacencyList;  // continentId -> list of it's neighbors id;
    bool continentEdgeExists(int continentId1, int continentId2);
    void addContinentEdges(int territoryId1, int territoryId2);
    void dfsTerritories(unordered_map<int, bool> &visited, int territoryId);
    void dfsContinents(unordered_map<int, bool> &visited, int continentId);
    bool validateTerritories();
    bool validateContinents();
};

