//
// Created by Luojia yan on 2021-02-07.
//


#include "Map.h"
#include "iostream"
#include <sstream>
using namespace std;


Territory::~Territory(){}
Territory:: Territory(int id, string& newName, int continentId) {
    this->id = id;
    this->name = newName;
    this->continentId = continentId;
}

Territory::Territory(const Territory& territory) {
    name = territory.name;
    id = territory.id;
    continentId = territory.continentId;
    armies = territory.armies;
    cities = territory.cities;
}

Territory &Territory::operator=(const Territory &territory) {
    name = territory.name;
    id = territory.id;
    continentId = territory.continentId;
    armies = territory.armies;
    cities = territory.cities;
    return *this;
}

ostream &operator<<(ostream &out, const Territory &territory) {
    out << "Territory{ firstName=" << territory.name << "; ";
    out << "id=" << territory.id << "; ";
    out << "continentId=" << territory.continentId << "; ";
    out << "armies={";
    for (const auto &[k, v] : territory.armies) {
        out << "Armies[" << k << "] = " << v << "; ";
    }
    out << "};  cities={";
    for (const auto &[k, v] : territory.cities) {
        out << "Cities[" << k << "] = " << v << "; ";
    }
    out << "}";
    return out;
}

int Territory::getId() const {
    return this->id;
}

void Territory::setId(int newId) {
    id = newId;
}

string Territory::getName() const {
    return name;
}

void Territory::setName(const string &newName) {
    name = newName;
}

int Territory::getContinentId() const {
    return this->continentId;
}

void Territory::setContinentId(const int newContinentId) {
    this->continentId = newContinentId;
}

int Territory::getArmiesOfPlayer(int playerId) {
    if (armies.find(playerId) == armies.end()) {
        return 0;
    }
    return armies[playerId];
}

void Territory::placeNewArmiesOfPlayer(int playerId, int numOfNewArmies) {
    armies[playerId] += numOfNewArmies;
}

void Territory::removeArmiesOfPlayer(int playerId, int numOfArmiesToRemove) {
    if (armies.find(playerId) == armies.end()) {
        return;
    }
    if (armies[playerId] < numOfArmiesToRemove) {
        cout << "No enough armies to remove!" << endl;
        return;
    }
    armies[playerId] -= numOfArmiesToRemove;
}

void Territory::displayCityInfo() {
    cout << "The following players has built city here: " << endl;
    for (const auto &[k, v] : cities) {
        if (v) {
            cout << "Player " << k << endl;
        }
    }
}

void Territory::buildCity(int playerId) {
    cities[playerId]++;
}

int Territory::getControllingPlayerId() {
    int playerId = -1;
    int max = 0;
    for (const auto &[k, v] : armies) {
        int army = v;
        if (cities[k]) {
            army++;
        }
        if (army > max) {
            max = army;
            playerId = k;
        } else if (army == max) {
            playerId = -1;
        }
    }
    return playerId;
}

void Territory::printTerritory() {
    // TODO: Print all the info of this territory in a table
}


string Territory::toString() const {
    stringstream ss;
    ss << "Territory{ firstName=" << name << "; ";
    ss << "id=" << id << "; ";
    ss << "continentId=" << continentId << "; ";
    ss << "armies={";
    for (const auto &[k, v] : armies) {
        ss << "Armies[" << k << "] = " << v << " " << endl;
    }
    for (const auto &[k, v] : cities) {
        ss << "Cities[" << k << "] = " << v << " " << endl;
    }
    return ss.str();
}

unordered_map<int, int> &Territory::getArmies() {
    return armies;
}

unordered_map<int, int> &Territory::getCities() {
    return cities;
}

Continent::Continent(int id, string& name) {
    this->id = id;
    this->name = name;
}

Continent::Continent(const Continent& continent) {
    id = continent.id;
    name = continent.name;
    territories = continent.territories;
}

Continent::~Continent() {}

Continent &Continent::operator=(const Continent &continent) {
    id = continent.id;
    name = continent.name;
    territories = continent.territories;
    return *this;
}

ostream &operator<<(ostream &out, const Continent &continent) {
    out << "Continent{ Name=" << continent.name << "; ";
    out << "continentId=" << continent.id << "; ";
    out << "territories=[";
    for (int i = 0; i < continent.territories.size(); i++) {
        out << *continent.territories[i];
        if (i < continent.territories.size() - 1) {
            out << ", ";
        }
    }
    out << "]}";
    return out;
}

int Continent::getId() const {
    return id;
}

void Continent::setId(int newId) {
    this->id = newId;
}

string Continent::getName() const {
    return name;
}

void Continent::setName(string& newName) {
    name = newName;
}

void Continent::addTerritory(Territory* Territory) {
    territories.emplace_back(Territory);
}

vector<int> Continent::getTerritoryIdList() {
    vector<int> list;
    for (auto & territory : territories) {
        list.emplace_back(territory->getId());
    }
    return list;
}

Territory *Continent::getTerritoryById(int id) const {
    for (auto & territory : territories) {
        if (territory->getId() == id) {
            return territory;
        }
    }
    return nullptr;
}

int Continent::getControllingPlayerId() const {
    unordered_map<int, int> armyAnyCity;
    for (auto & territory : territories) {
        for (const auto &[k, v] : territory->getArmies()) {
            armyAnyCity[k] += v;
            armyAnyCity[k] += territory->getCities()[k];
        }
    }
    int playerId = -1;
    int max = 0;
    for (const auto &[k, v] : armyAnyCity) {
        if (v > max) {
            max = v;
            playerId = k;
        } else if (v == max) {
            playerId = -1;
        }
    }
    return playerId;
}


Map::Map(int id, string& name) {
    this->id = id;
    this->name = name;
}

Map::~Map() {}


Map::Map(const Map& secondMap) {

}

Map &Map::operator=(const Map &secondMap) {


    return *this;
}

ostream &operator<<(ostream &out, const Map &outputMap) {
    out << "Map{ firstName=" << "; ";
    out << "continents=[";

    out << "]}";
    return out;
}

int Map::getId() const {
    return id;
}

void Map::setId(int newId) {
    id = newId;
}

string Map::getName() const {
    return name;
}

void Map::setName(string &newName) {
    name = newName;
}

vector<Continent *> &Map::getContinents() {
    return continents;
}

void Map::addContinent(Continent *newContinent) {
    continents.emplace_back(newContinent);
}

vector<Territory *> &Map::getTerritories() {
    return territories;
}

Territory *Map::getTerritoryById(int territoryId) {
    for (auto & territory : territories) {
        if (territory->getId() == territoryId) {
            return territory;
        }
    }
    return nullptr;
}

Continent *Map::getContinentById(int continentId) {
    for (auto & continent : continents) {
        if (continent->getId() == continentId) {
            return continent;
        }
    }
    return nullptr;
}


void Map::validate(Map* map){
    if(checkTerritoryBelongsToOneContinent(map)) {
        cout << endl << "Each country belongs to one and only one continent" << endl;
    } else {
        cout << "Each country does not belong only one continent" << endl;
    }
    if(validateTerritory()) {
        cout << "The map is connected graph" << endl;
    } else {
        cout << "The map is not connected graph" << endl;
    }
    if(validateContinent()) {
        cout << "The Continent graph is connected graph" << endl;
    } else {
        cout << "The Continent graph is not connected graph" << endl;
    }
}


bool Map::checkTerritoryBelongsToOneContinent(Map* map) {
    int error = 0;
    for(int i = 1; i <= continentMatrix.size(); i++) {
        Continent* continent = map->ReturnContinentHashMap()[i];
        string continentName = continent->getName();
        vector<Territory*> territories = continent->getTerritories();
        for(int j = 0; j < territories.size(); j++) {
            int continentNumber = territories[j]->getContinentId();
            string territoryName = territories[j]->getName();
            if (continentNumber != 0) {
                cout << territoryName << " only belongs to  " << continentName << endl;
            } else {
                error++;
                cout << territoryName << " does not belong to any continent "<< endl;
            }
        }
    }
    return error == 0;
}

void Map::addEdgesTerritory(int territoryId1, int territoryId2) {

}

bool Map::dfsValidate() {
    int numberOfTerritory = territoryMatrix.size();
    unordered_map<int, vector<int>> neighborsMap;
    for (int i = 0; i < territoryMatrix.size(); i++) {
        vector<int> neighbors;
        for (int j = 0; j < territoryMatrix.size(); j++) {
            if (territoryMatrix[i][j]) {
                neighbors.push_back(j + 1);
            }
        }
        neighborsMap[i + 1] = neighbors;
    }
    vector<bool> visited(numberOfTerritory, false);
    dfsTerritories(neighborsMap, visited, 1);
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i]) {
            cout << "DFS: This is not a connected map." << endl;
            return false;
        }
    }
    cout << "DFS: This is a connected map." << endl;
    return true;
}

void Map::dfs(unordered_map<int, vector<int> >& neighborsMap, vector<bool> &visited, int territoryNumber) {
    if (visited[territoryNumber - 1]) {
        return;
    }
    visited[territoryNumber - 1] = true;
    vector<int> neighbors = neighborsMap.at(territoryNumber);
    for (int i = 0; i < neighbors.size(); i++) {
        dfsTerritories(neighborsMap, visited, neighbors[i]);
    }
}








