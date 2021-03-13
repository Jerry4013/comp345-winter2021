//
// Created by Luojia yan on 2021-02-07.
//

#include "Map.h"
#include "iostream"
#include <sstream>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <iomanip>

using namespace std;


Territory::Territory(int id, string& newName, int continentId, int numOfPlayers) {
    this->id = id;
    this->name = newName;
    this->continentId = continentId;
    for (int i = 0; i < numOfPlayers; ++i) {
        armies[i + 1] = 0;
        cities[i + 1] = 0;
    }
}

Territory::~Territory() {
    // No pointer to delete;
}

Territory::Territory(const Territory& territory) {
    id = territory.id;
    name = territory.name;
    continentId = territory.continentId;
    armies = territory.armies;
    cities = territory.cities;
}

Territory &Territory::operator=(const Territory &territory) {
    id = territory.id;
    name = territory.name;
    continentId = territory.continentId;
    armies = territory.armies;
    cities = territory.cities;
    return *this;
}

ostream &operator<<(ostream &out, const Territory &territory) {
    out << "Territory" << endl;
    out << "ID: " << territory.id << "\tName: " << territory.name << "\tContinent ID: " << territory.continentId << endl;
    out << "------------------------------------------" << endl;
    out << setw(8) << "" << setw(10) << "Armies" << setw(10) << "Cities" << endl;
    map<int, int> cities = territory.cities;
    for (auto &[k, v] : territory.armies) {
        out << "player " << k << setw(10) << v << setw(10) << cities[k] << endl;
    }
    out << "\n\n";
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
    cout << "Territory" << endl;
    cout << "ID: " << id << "\tName: " << name << "\tContinent ID: " << continentId << endl;
    cout << "------------------------------------------" << endl;
    cout << setw(8) << "" << setw(10) << "Armies" << setw(10) << "Cities" << endl;
    for (const auto &[k, v] : armies) {
        cout << "player " << k << setw(10) << v << setw(10) << cities[k] << endl;
    }
    cout << "\n\n";
}

map<int, int> &Territory::getArmies() {
    return armies;
}

map<int, int> &Territory::getCities() {
    return cities;
}


Continent::Continent(int id, string& name, int mapId) {
    this->id = id;
    this->name = name;
    this->mapId = mapId;
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

int Continent::getMapId() const {
    return mapId;
}

void Continent::setMapId(int newMapId) {
    this->mapId = newMapId;
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

void Continent::printContinent() {
    vector<int> territoryIdList = getTerritoryIdList();
    cout << "Continent" << endl;
    cout << "ID: " << id << "\tName: " << name << "\tMap ID: " << mapId << endl;
    cout << "------------------------------------------" << endl;
    cout << "Territories: [";
    for (int i = 0; i < territoryIdList.size(); ++i) {
        cout << territoryIdList[i];
        if (i != territoryIdList.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]\n\n" << endl;
}

Territory *Continent::getTerritoryById(int territoryId) const {
    for (auto & territory : territories) {
        if (territory->getId() == territoryId) {
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

Map::~Map() {
    // All the pointers are not created in the constructor.
}


Map::Map(const Map& secondMap) {
    id = secondMap.id;
    name = secondMap.name;
    territories = secondMap.territories;
    continents = secondMap.continents;
    territoryAdjacencyList = secondMap.territoryAdjacencyList;
    continentAdjacencyList = secondMap.continentAdjacencyList;
}

Map &Map::operator=(const Map &secondMap) {
    id = secondMap.id;
    name = secondMap.name;
    territories = secondMap.territories;
    continents = secondMap.continents;
    territoryAdjacencyList = secondMap.territoryAdjacencyList;
    continentAdjacencyList = secondMap.continentAdjacencyList;
    return *this;
}

ostream &operator<<(ostream &out, const Map &outputMap) {
    out << "Map" << endl;
    out << "ID: " << outputMap.id << "\tName: " << outputMap.name << endl;
    out << "------------------------------------------" << endl;
    out << "Territories: [";
    for (int i = 0; i < outputMap.territories.size(); ++i) {
        out << outputMap.territories[i]->getId();
        if (i != outputMap.territories.size() - 1) {
            out << ", ";
        }
    }
    out << "]\n" << endl;
    out << "Continents: [";
    for (int i = 0; i < outputMap.continents.size(); ++i) {
        out << outputMap.continents[i]->getId();
        if (i != outputMap.continents.size() - 1) {
            out << ", ";
        }
    }
    out << "]\n" << endl;
    out << "Territory neighbors:" << endl;
    for (const auto &[k, v] : outputMap.territoryAdjacencyList) {
        out << k << " -> [";
        for (int i = 0; i < v.size(); i++) {
            out << v[i];
            if (i != v.size() - 1) {
                out << ", ";
            }
        }
        out << "]" << endl;
    }
    out << "\nContinent neighbors:" << endl;
    for (const auto &[k, v] : outputMap.continentAdjacencyList) {
        out << k << " -> [";
        for (int i = 0; i < v.size(); i++) {
            out << v[i];
            if (i != v.size() - 1) {
                out << ", ";
            }
        }
        out << "]" << endl;
    }
    out << "\n\n";
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

void Map::addTerritory(Territory* newTerritory) {
    territories.emplace_back(newTerritory);
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

vector<int> &Map::getTerritoryNeighborsById(int territoryId) {
    return territoryAdjacencyList[territoryId];
}

vector<int> &Map::getContinentNeighborsById(int continentId) {
    return continentAdjacencyList[continentId];
}

bool Map::edgeExists(int territoryId1, int territoryId2) {
    if (territoryAdjacencyList.find(territoryId1) == territoryAdjacencyList.end() ||
        territoryAdjacencyList.find(territoryId2) == territoryAdjacencyList.end()) {
        return false;
    }
    vector<int> neighborsOfTerritory1 = territoryAdjacencyList[territoryId1];
    for (int neighbor : neighborsOfTerritory1) {
        if (neighbor == territoryId2) {
            return true;
        }
    }
    return false;
}

void Map::addTerritoryEdges(int territoryId1, int territoryId2) {
    if (edgeExists(territoryId1, territoryId2)) {
        return;
    }
    if (territoryAdjacencyList.find(territoryId1) == territoryAdjacencyList.end()) {
        vector<int> neighborsOfTerritory1;
        neighborsOfTerritory1.emplace_back(territoryId2);
        territoryAdjacencyList[territoryId1] = neighborsOfTerritory1;
    } else {
        territoryAdjacencyList[territoryId1].emplace_back(territoryId2);
    }
    if (territoryAdjacencyList.find(territoryId2) == territoryAdjacencyList.end()) {
        vector<int> neighborsOfTerritory2;
        neighborsOfTerritory2.emplace_back(territoryId1);
        territoryAdjacencyList[territoryId2] = neighborsOfTerritory2;
    } else {
        territoryAdjacencyList[territoryId2].emplace_back(territoryId1);
    }
    addContinentEdges(territoryId1, territoryId2);
}

bool Map::continentEdgeExists(int continentId1, int continentId2) {
    if (continentAdjacencyList.find(continentId1) == continentAdjacencyList.end() ||
        continentAdjacencyList.find(continentId2) == continentAdjacencyList.end()) {
        return false;
    }
    vector<int> neighborsOfContinent1 = continentAdjacencyList[continentId1];
    for (int neighbor : neighborsOfContinent1) {
        if (neighbor == continentId2) {
            return true;
        }
    }
    return false;
}

void Map::addContinentEdges(int territoryId1, int territoryId2) {
    int continentId1 = getTerritoryById(territoryId1)->getContinentId();
    int continentId2 = getTerritoryById(territoryId2)->getContinentId();
    if (continentId1 == continentId2 || continentEdgeExists(continentId1, continentId2)) {
        return;
    }
    if (continentAdjacencyList.find(continentId1) == continentAdjacencyList.end()) {
        vector<int> neighborsOfContinent1;
        neighborsOfContinent1.emplace_back(continentId2);
        continentAdjacencyList[continentId1] = neighborsOfContinent1;
    } else {
        continentAdjacencyList[continentId1].emplace_back(continentId2);
    }
    if (continentAdjacencyList.find(continentId2) == continentAdjacencyList.end()) {
        vector<int> neighborsOfContinent2;
        neighborsOfContinent2.emplace_back(continentId1);
        continentAdjacencyList[continentId2] = neighborsOfContinent2;
    } else {
        continentAdjacencyList[continentId2].emplace_back(continentId1);
    }
}

void Map::addMultiEdges(int territoryId1, vector<int> &neighbors) {
    //TODO: 方便给一个territory一次性添加多条边
}

int Map::getDistance(int territoryId1, int territoryId2) {
    if (territoryAdjacencyList.find(territoryId1) == territoryAdjacencyList.end()) {
        return -1;
    }
    int continentId1 = getTerritoryById(territoryId1)->getContinentId();
    int continentId2 = getTerritoryById(territoryId2)->getContinentId();
    if (continentId1 == continentId2) {
        return 1;
    }
    return 3;
}

void Map::printTerritoryAdjacencyList() {
    cout << "Territory neighbors:" << endl;
    cout << "------------------------------------------" << endl;
    for (const auto &[k, v] : territoryAdjacencyList) {
        cout << "Territory " << k << " -> [";
        for (int i = 0; i < v.size(); i++) {
            cout << v[i];
            if (i != v.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
    cout << "\n\n" << endl;
}

void Map::printContinentAdjacencyList() {
    cout << "Continent neighbors:" << endl;
    cout << "------------------------------------------" << endl;
    for (const auto &[k, v] : continentAdjacencyList) {
        cout << "Continent " << k << " -> [";
        for (int i = 0; i < v.size(); i++) {
            cout << v[i];
            if (i != v.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
    cout << "\n\n" << endl;
}

bool Map::validate() {
    if(checkTerritoryBelongsToOneContinent() && validateTerritories() && validateContinents()) {
        cout << "This map is valid." << endl;
        return true;
    }
    cout << "This map is not valid." << endl;
    return false;
}

bool Map::checkTerritoryBelongsToOneContinent() {
    for (auto & territory : territories) {
        if (getContinentById(territory->getContinentId()) == nullptr) {
            cout << territory->getName() << " does not belong any continent." << endl;
            return false;
        }
    }
    unordered_set<int> allTerritories;
    for (auto & continent : continents) {
        vector<int> territoryIdList = continent->getTerritoryIdList();
        for (int territoryId : territoryIdList) {
            if (allTerritories.find(territoryId) != allTerritories.end()) {
                cout << getTerritoryById(territoryId)->getName() << " belongs to more than one continent! Error!" << endl;
                return false;
            }
            allTerritories.insert(territoryId);
        }
    }
    cout << "Each territory belongs to one and only one continent." << endl;
    return allTerritories.size() == territories.size();
}

bool Map::validateTerritories() {
    int numberOfTerritory = territories.size();
    if (numberOfTerritory == 0) {
        return true;
    }
    unordered_map<int, bool> visited;
    for (auto & territory : territories) {
        visited[territory->getId()] = false;
    }
    dfsTerritories(visited, territories[0]->getId());
    for (const auto &[k, v] : visited) {
        if (!v) {
            cout << "DFS for Territories: This is not a connected map." << endl;
            return false;
        }
    }
    cout << "DFS for Territories: This is a connected map." << endl;
    return true;
}

bool Map::validateContinents() {
    int numberOfContinents = continents.size();
    if (numberOfContinents == 0) {
        return true;
    }
    unordered_map<int, bool> visited;
    for (auto & continent : continents) {
        visited[continent->getId()] = false;
    }
    dfsContinents(visited, continents[0]->getId());
    for (const auto &[k, v] : visited) {
        if (!v) {
            cout << "DFS for Continents: This is not a connected map." << endl;
            return false;
        }
    }
    cout << "DFS for Continents: This is a connected map." << endl;
    return true;
}

void Map::dfsTerritories(unordered_map<int, bool> &visited, int territoryId) {
    if (visited[territoryId]) {
        return;
    }
    visited[territoryId] = true;
    vector<int> neighbors = territoryAdjacencyList[territoryId];
    for (int neighbor : neighbors) {
        dfsTerritories(visited, neighbor);
    }
}

void Map::dfsContinents(unordered_map<int, bool> &visited, int continentId) {
    if (visited[continentId]) {
        return;
    }
    visited[continentId] = true;
    vector<int> neighbors = continentAdjacencyList[continentId];
    for (int neighbor : neighbors) {
        dfsContinents(visited, neighbor);
    }
}

Map* Map::extend(Map* secondMap, int port1, int port2, int newId, string& newName) {
    // TODO: 函数内部新建对象，怎么销毁？能不能传出去？
    Map* largerMap = new Map(newId, newName);
    largerMap->territories = territories;
    for (auto & territory : secondMap->getTerritories()) {
        largerMap->territories.emplace_back(territory);
    }
    return largerMap;
}
