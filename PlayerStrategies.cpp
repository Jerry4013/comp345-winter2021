//
// Created by jerry on 4/3/2021.
//

#include "PlayerStrategies.h"
#include <algorithm>

Territory *PlayerStrategy::getTerritoryById(int territoryId, vector<Territory *> &territories) {
    for (auto & territory : territories) {
        if (territory->getId() == territoryId) {
            return territory;
        }
    }
    cout << "ERROR! There is no territory with this ID." << endl;
    return nullptr;
}

void PlayerStrategy::printNeighborsOfTerritoriesWithArmies(int id, vector<Territory *> &territories,
                                                           map<int, vector<int>> &territoryAdjacencyList) {
    cout << "Neighbors of my territories: " << endl;
    for (auto & territory : territories) {
        int numOfArmies = territory->getArmies()[id];
        if (numOfArmies > 0) {
            cout << "Territory" << territory->getId() << " (" << numOfArmies << " armies) -> ";
            vector<int> neighbors = territoryAdjacencyList[territory->getId()];
            for (int neighbor : neighbors) {
                int distance = 1;
                if (territory->getContinentId() != getTerritoryById(neighbor, territories)->getContinentId()) {
                    distance = 3;
                }
                cout << "Territory" << neighbor << " (distance " << distance << "), ";
            }
            cout << endl;
        }
    }
}

int HumanStrategy::selectCard(Hand *hand, int coins) {
    int cardIndex;
    while (true) {
        cout << "Please select a card index (1-6) (You have " << coins << " coins):" << endl;
        cout << ">> ";
        cin >> cardIndex;
        cardIndex--;
        if (cardIndex < 0 || cardIndex >= Hand::CARD_COSTS_SIZE) {
            cout << "ERROR! Please enter a number from range 1-6!" << endl;
            cout << "Try again." << endl;
            continue;
        }
        if (coins < Hand::CARD_COSTS[cardIndex]) {
            cout << "ERROR! You don't have enough coin to buy this card!" << endl;
            cout << "Try again." << endl;
            continue;
        }
        break;
    }
    return cardIndex;
}

string HumanStrategy::toString() {
    return "Human Strategy";
}

void HumanStrategy::takeAction(Action action, int id, vector<Territory*>& territories, int &remainingCubesRef,
                               map<int, vector<int>> territoryAdjacencyList, int flyAbility, int &remainingCity,
                               map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap) {
    while (action.amount > 0) {
        int option;
        cout << "--------------------------------------" << endl;
        cout << "You can " << action << ". (You are player " << id << ")" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Please choose one option:" << endl;
        cout << "1. Take action." << endl;
        cout << "2. Done." << endl;
        cout << ">>";
        cin >> option;
        if (option == 2) {
            break;
        }
        int remainingPoints = action.amount;
        if (action.actionType == ActionType::placeArmy) {
            remainingPoints = placeNewArmiesPrompt(id, action.amount, territories, remainingCubesRef);
        } else if (action.actionType == ActionType::moveArmy) {
            remainingPoints = moveArmiesPrompt(id, action.amount, territories, territoryAdjacencyList, flyAbility);
        } else if (action.actionType == ActionType::buildCity) {
            remainingPoints = buildCityPrompt(id, action.amount, territories, remainingCity);
        } else if (action.actionType == ActionType::destroyArmy) {
            remainingPoints = destroyArmyPrompt(action.amount, territories, remainingCubesMap, immuneAttackMap);
        }
        if (remainingPoints == action.amount) {
            continue;
        }
        action.amount = remainingPoints;
    }
}

int HumanStrategy::placeNewArmiesPrompt(int id, int movingPoints, vector<Territory*>& territories,
                                        int &remainingCubesRef) {
    cout << "Game rule: You may place new armies only on the starting region or on a region where you have a city."
         << endl;
    printTerritoriesForNewArmies(id, territories);
    int territoryId, numberOfArmies;
    cout << "Please choose a territory ID to place the new armies: " << endl;
    cout << ">>";
    cin >> territoryId;

    // You may place new armies only on the starting region or on a region where you have a city.
    Territory* territory = getTerritoryById(territoryId, territories);
    if (!territory->getIsStartingRegion() && territory->getCities()[id] == 0) {
        cout << "ERROR! You may place new armies only on the starting region or on a region where"
                " you have a city." << endl;
        return movingPoints;
    }

    cout << "Please enter the number of armies to place: " << endl;
    cout << ">>";
    cin >> numberOfArmies;
    if (numberOfArmies > movingPoints) {
        cout << "ERROR! You can place " << movingPoints << " new armies at most." << endl;
    } else if (numberOfArmies < 1) {
        cout << "ERROR! Please select a valid number." << endl;
    } else if (remainingCubesRef < numberOfArmies) {
        cout << "ERROR! You don't have enough cubes in hand!" << endl;
    } else {
        PlaceNewArmies(id, numberOfArmies, territory, remainingCubesRef);
        movingPoints -= numberOfArmies;
    }
    return movingPoints;
}

void HumanStrategy::printTerritoriesForNewArmies(int id, vector<Territory *>& territories) {
    cout << "You may place new armies in these territories: ";
    for (auto & territory : territories) {
        if (territory->getIsStartingRegion() || territory->getCities()[id] > 0) {
            cout << territory->getId() << ", ";
        }
    }
    cout << endl;
}

void HumanStrategy::PlaceNewArmies(int id, int numberOfNewArmies, Territory *territory, int &remainingCubesRef) {
    territory->placeNewArmiesOfPlayer(id, numberOfNewArmies);
    remainingCubesRef -= numberOfNewArmies;
    cout << "Player " << id << " place " << numberOfNewArmies << " new armies in territory " << territory->getId()
         << endl;
    cout << "Your remaining cubes is " << remainingCubesRef << endl;
}

int HumanStrategy::moveArmiesPrompt(int id, int movingPoints, vector<Territory *> &territories,
                                    map<int, vector<int>> &territoryAdjacencyList, int flyAbility) {
    printMyTerritoriesWithArmies(id, territories);
    printNeighborsOfTerritoriesWithArmies(id, territories, territoryAdjacencyList);
    vector<int> myTerritoriesWithArmies;
    for (auto & territory : territories) {
        if (territory->getArmies()[id] > 0) {
            myTerritoriesWithArmies.emplace_back(territory->getId());
        }
    }
    vector<int> territoryIdList;
    territoryIdList.reserve(territories.size());
    for (auto & territory : territories) {
        territoryIdList.emplace_back(territory->getId());
    }
    int fromTerritoryId, toTerritoryId, numberOfArmies;
    cout << "Please choose a territory ID as starting point: " << endl;
    cout << ">>";
    cin >> fromTerritoryId;
    while (find(myTerritoriesWithArmies.begin(), myTerritoriesWithArmies.end(), fromTerritoryId) ==
           myTerritoriesWithArmies.end()) {
        cout << "ERROR! You don't have army at this territory. Please try again!" << endl;
        cout << ">>";
        cin >> fromTerritoryId;
    }
    cout << "Please choose a territory ID as target: " << endl;
    cout << ">>";
    cin >> toTerritoryId;
    while (find(territoryIdList.begin(), territoryIdList.end(), toTerritoryId) == territoryIdList.end()) {
        cout << "ERROR! There is no territory with this ID. Please try again." << endl;
        cout << ">>";
        cin >> toTerritoryId;
    }
    Territory* fromTerritory = getTerritoryById(fromTerritoryId, territories);
    Territory* toTerritory = getTerritoryById(toTerritoryId, territories);
    vector<int> neighbors = territoryAdjacencyList[fromTerritoryId];
    while (find(neighbors.begin(), neighbors.end(), toTerritoryId) == neighbors.end()) {
        cout << "ERROR! These two territories are not connected. Please try again." << endl;
        cout << "Please choose a territory ID as starting point: " << endl;
        cout << ">>";
        cin >> fromTerritoryId;
        cout << "Please choose a territory ID as target: " << endl;
        cout << ">>";
        cin >> toTerritoryId;
        fromTerritory = getTerritoryById(fromTerritoryId, territories);
        toTerritory = getTerritoryById(toTerritoryId, territories);
    }
    cout << "Please choose the number of armies you want to move: " << endl;
    cout << ">>";
    cin >> numberOfArmies;
    while (numberOfArmies > fromTerritory->getArmiesOfPlayer(id)) {
        cout << "ERROR! You can move at most " << fromTerritory->getArmiesOfPlayer(id) << " armies. Please try again."
             << endl;
        cout << ">>";
        cin >> numberOfArmies;
    }
    int remainingMovingPoints = MoveArmies(id, numberOfArmies, fromTerritory, toTerritory, movingPoints, flyAbility);
    return remainingMovingPoints;
}

int HumanStrategy::destroyArmyPrompt(int destroyPoints, vector<Territory*>& territories,
                                     map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap) {
    int playerId, territoryId;
    cout << "Please choose a player ID to destroy army: " << endl;
    cout << ">>";
    cin >> playerId;
    if (immuneAttackMap[playerId] > 0) {
        cout << "This player is immune to attack!" << endl;
        return destroyPoints;
    }
    cout << "This player has armies in the following regions:" << endl;
    for (auto & territory : territories) {
        int numOfArmies = territory->getArmiesOfPlayer(playerId);
        if (numOfArmies > 0) {
            cout << "TerritoryId " << territory->getId() << ": " << numOfArmies << " armies; ";
        }
    }
    cout << endl;
    cout << "Please choose a territory ID to destroy the army: " << endl;
    cout << ">>";
    cin >> territoryId;

    Territory* territory = getTerritoryById(territoryId, territories);
    int remainingMovingPoints = DestroyArmy(playerId, 1, territory, remainingCubesMap,
                                            destroyPoints);
    return remainingMovingPoints;
}

int HumanStrategy::buildCity(int id, Territory* territory, int buildPoints, int &remainingCity) {
    if (remainingCity <= 0) {
        cout << "You have no city in hand!" << endl;
        return buildPoints;
    }
    remainingCity--;
    territory->buildCity(id);
    return buildPoints - 1;
}

void HumanStrategy::printMyTerritoriesWithArmies(int id, vector<Territory *> &territories) {
    cout << "My Territories With Armies:" << endl;
    for (auto & territory : territories) {
        if (territory->getArmies()[id] > 0) {
            cout << "Territory" << territory->getId() << " (" << territory->getArmies()[id] << " armies), ";
        }
    }
    cout << endl;
}

int HumanStrategy::MoveArmies(int id, int numberOfArmies, Territory *from, Territory *to, int movingPoints,
                              int flyAbility) {
    int remainingPoints;
    if (from->getContinentId() == to->getContinentId()) {
        remainingPoints = MoveOverLand(numberOfArmies, movingPoints);
    } else {
        remainingPoints = MoveOverWater(numberOfArmies, movingPoints, flyAbility);
    }
    if (remainingPoints == movingPoints) {
        return remainingPoints;
    }
    from->removeArmiesOfPlayer(id, numberOfArmies);
    to->placeNewArmiesOfPlayer(id, numberOfArmies);
    cout << numberOfArmies << " armies were moved from " << from->getId() << " to " << to->getId() << endl;
    return remainingPoints;
}

int HumanStrategy::MoveOverLand(int numberOfArmies, int movingPoints) {
    if (numberOfArmies > movingPoints) {
        cout << "ERROR! You don't have enough moving points. Please try again." << endl;
        return movingPoints;
    }
    return movingPoints - numberOfArmies;
}

int HumanStrategy::MoveOverWater(int numberOfArmies, int movingPoints, int flyAbility) {
    int cost = 3;
    if (flyAbility == 1) {
        cout << "\nFlying level 1! The cost to move over water is 2 per army." << endl;
        cost = 2;
    } else if (flyAbility >= 2) {
        cout << "\nFlying level 2! The cost to move over water is 1 per army." << endl;
        cost = 1;
    }
    if (numberOfArmies * cost > movingPoints) {
        cout << "ERROR! You don't have enough moving points. Try again." << endl;
        return movingPoints;
    }
    return movingPoints - numberOfArmies * cost;
}

int HumanStrategy::buildCityPrompt(int id, int buildPoints, vector<Territory *> &territories, int &remainingCity) {
    cout << "Game rule: You may place a city anywhere on the board where you have an army." << endl;
    printMyTerritoriesWithArmies(id, territories);
    vector<int> myTerritoriesWithArmies;
    for (auto & territory : territories) {
        if (territory->getArmies()[id] > 0) {
            myTerritoriesWithArmies.emplace_back(territory->getId());
        }
    }
    int territoryId;
    cout << "Please choose a territory ID to build a city: " << endl;
    cout << ">>";
    cin >> territoryId;
    while (find(myTerritoriesWithArmies.begin(), myTerritoriesWithArmies.end(), territoryId) == myTerritoriesWithArmies.end()) {
        cout << "ERROR! You may place a city where you have an army. Please try again!" << endl;
        cout << ">>";
        cin >> territoryId;
    }
    Territory* territory = getTerritoryById(territoryId, territories);
    return buildCity(id, territory, buildPoints, remainingCity);
}

int HumanStrategy::DestroyArmy(int otherPlayerId, int numberOfArmies, Territory *territory,
                               map<int, int*>& remainingCubesMap, int destroyPoints) {
    int currTroops = territory->getArmiesOfPlayer(otherPlayerId);
    if (currTroops < numberOfArmies) {
        cout << "There is not enough troop to destroy!" << endl;
        return destroyPoints;
    }
    *remainingCubesMap[otherPlayerId] += numberOfArmies;
    territory->removeArmiesOfPlayer(otherPlayerId, numberOfArmies);
    cout << numberOfArmies << " armies are destroyed on territory " << territory->getId() << endl;
    return destroyPoints - numberOfArmies;
}

int HumanStrategy::selectOrCard(Card *card) {
    int option;
    cout << "You may choose one action below: " << endl;
    cout << "1. " << card->getActions()[0] << endl;
    cout << "2. " << card->getActions()[1] << endl;
    cout << ">>";
    cin >> option;
    while (option < 1 || option > 2) {
        cout << "Invalid number! Please try again." << endl;
        cout << ">>";
        cin >> option;
    }
    return option;
}

int GreedyComputerStrategy::selectCard(Hand *hand, int coins) {
    for (int cardIndex = 0; cardIndex < hand->getHandCards().size() && coins >= Hand::CARD_COSTS[cardIndex]; ++cardIndex) {
        for (int j = 0; j < hand->getHandCards()[cardIndex]->getActions().size(); ++j) {
            ActionType actionType = hand->getHandCards()[cardIndex]->getActions()[j].actionType;
            if (actionType == ActionType::buildCity || actionType == ActionType::destroyArmy) {
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "The greedy computer selected card " << cardIndex + 1 << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                return cardIndex;
            }
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "No card can build a city or destroy an army with your coins. " << endl;
    cout << "The greedy computer selected card 1 by default." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    return 0;
}

string GreedyComputerStrategy::toString() {
    return "Greedy Computer Strategy";
}

void GreedyComputerStrategy::takeAction(Action action, int id, vector<Territory *> &territories, int &remainingCubesRef,
                                        map<int, vector<int>> territoryAdjacencyList, int flyAbility, int &remainingCity,
                                        map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap) {
    cout << "--------------------------------------" << endl;
    cout << "You can " << action << ". (You are player " << id << ")" << endl;
    cout << "--------------------------------------" << endl;
    if (action.actionType == ActionType::placeArmy) {
        greedyPlaceNewArmies(id, action.amount, territories, remainingCubesRef);
    } else if (action.actionType == ActionType::moveArmy) {
        greedyMoveArmies(id, action.amount, territories, territoryAdjacencyList, flyAbility);
    } else if (action.actionType == ActionType::buildCity) {
        greedyBuildCity(id, territories, remainingCity);
    } else if (action.actionType == ActionType::destroyArmy) {
        greedyDestroyArmy(id, territories, remainingCubesMap, immuneAttackMap);
    }
}

int GreedyComputerStrategy::selectOrCard(Card *card) {
    for (int i = 0; i < card->getActions().size(); ++i) {
        ActionType actionType = card->getActions()[i].actionType;
        if (actionType == ActionType::buildCity || actionType == ActionType::destroyArmy) {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "The greedy computer selected action " << i + 1 << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return i + 1;
        }
    }
    return 1;
}

void GreedyComputerStrategy::greedyPlaceNewArmies(int id, int movingPoints, vector<Territory*>& territories,
                                                 int &remainingCubesRef) {
    cout << "Game rule: You may place new armies only on the starting region or on a region where you have a city."
         << endl;
    cout << "You may place new armies in these territories: ";
    map<int, int> validTerritories; // territoryId -> the number of armies placed
    for (auto & territory : territories) {
        if (territory->getIsStartingRegion() || territory->getCities()[id] > 0) {
            cout << territory->getId() << ", ";
            validTerritories[territory->getId()] = 0;
        }
    }
    cout << endl;
    while (movingPoints > 0) {
        for (auto &[k, v] : validTerritories) {
            Territory* territory = getTerritoryById(k, territories);
            territory->placeNewArmiesOfPlayer(id, 1);
            validTerritories[k]++;
            movingPoints--;
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "The greedy computer " << id << " places ";
    for (auto &[k, v] : validTerritories) {
        cout << v << " armies at Territory " << k << "; ";
    }
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void GreedyComputerStrategy::greedyMoveArmies(int id, int movingPoints, vector<Territory *> &territories,
                                             map<int, vector<int>> &territoryAdjacencyList, int flyAbility) {
    printNeighborsOfTerritoriesWithArmies(id, territories, territoryAdjacencyList);
    int lastMovingPoint = movingPoints;
    while (movingPoints > 0) {
        for (auto & territory : territories) {
            int numOfArmies = territory->getArmies()[id];
            if (numOfArmies > 0) {
                vector<int> neighbors = territoryAdjacencyList[territory->getId()];
                for (int neighbor : neighbors) {
                    int distance = 1;
                    Territory* neighborTerritory = getTerritoryById(neighbor, territories);
                    if (territory->getContinentId() != neighborTerritory->getContinentId()) {
                        distance = 3;
                    }
                    int cost = distance;
                    if (distance == 3) {
                        if (flyAbility == 1) {
                            cout << "\nFlying level 1! The cost to move over water is 2 per army." << endl;
                            cost = 2;
                        } else if (flyAbility >= 2) {
                            cout << "\nFlying level 2! The cost to move over water is 1 per army." << endl;
                            cost = 1;
                        }
                    }
                    if (numOfArmies > 1 && neighborTerritory->getArmies()[id] < numOfArmies && movingPoints >= cost) {
                        territory->removeArmiesOfPlayer(id, 1);
                        neighborTerritory->placeNewArmiesOfPlayer(id, 1);
                        movingPoints -= cost;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        cout << "The greedy computer " << id << " moved 1 army from " << territory->getId()
                         << " to " << neighborTerritory->getId() << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    }
                }
                cout << endl;
            }
        }
        if (lastMovingPoint == movingPoints) {
            break;
        }
        lastMovingPoint = movingPoints;
    }
}

void GreedyComputerStrategy::greedyBuildCity(int id, vector<Territory *> &territories, int &remainingCity) {
    if (remainingCity <= 0) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "You have no city piece in hand! Do nothing." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return;
    }
    cout << "Game rule: You may place a city anywhere on the board where you have an army." << endl;
    vector<Territory*> myTerritoriesWithArmies;
    cout << "My Territories With Armies:" << endl;
    for (auto & territory : territories) {
        if (territory->getArmies()[id] > 0) {
            myTerritoriesWithArmies.emplace_back(territory);
            cout << "Territory" << territory->getId() << " (" << territory->getArmies()[id] << " armies), ";
        }
    }
    cout << endl;
    if (myTerritoriesWithArmies.empty()) {
        cout << "You don't have any army, so you can't build a city." << endl;
        return;
    }
    remainingCity--;
    for (auto & territory : myTerritoriesWithArmies) {
        if (!territory->getIsStartingRegion()) {
            territory->buildCity(id);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "The greedy computer " << id << " builds a city at territory " << territory->getId() << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return;
        }
    }
    myTerritoriesWithArmies[0]->buildCity(id);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "The greedy computer " << id << " builds a city at territory " << myTerritoriesWithArmies[0]->getId() << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void GreedyComputerStrategy::greedyDestroyArmy(int id, vector<Territory *> &territories,
                                              map<int, int *> &remainingCubesMap, map<int, int> &immuneAttackMap) {
    int playerIdToDestroy = -1;
    for (int i = 1; i <= 4; ++i) {
        if (i != id && immuneAttackMap[i] == 0) {
            for (auto & territory : territories) {
                int numOfArmies = territory->getArmiesOfPlayer(i);
                if (numOfArmies > 0) {
                    playerIdToDestroy = i;
                    *remainingCubesMap[playerIdToDestroy] += 1;
                    territory->removeArmiesOfPlayer(playerIdToDestroy, 1);
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    cout << "The greedy computer " << id << " destroyed 1 army of player " << playerIdToDestroy
                        << " at territory " << territory->getId() << endl;
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    return;
                }
            }
        }
    }
    cout << "Other players are all immune attack or have no army to destroy. Do nothing." << endl;
}

int ModerateComputerStrategy::selectCard(Hand *hand, int coins) {
    for (int cardIndex = 0; cardIndex < hand->getHandCards().size() && coins >= Hand::CARD_COSTS[cardIndex]; ++cardIndex) {
        for (int j = 0; j < hand->getHandCards()[cardIndex]->getActions().size(); ++j) {
            ActionType actionType = hand->getHandCards()[cardIndex]->getActions()[j].actionType;
            if (actionType == ActionType::moveArmy || actionType == ActionType::placeArmy) {
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "The moderate computer selected card " << cardIndex + 1 << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                return cardIndex;
            }
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "No card can move an army or place an army with your coins. " << endl;
    cout << "The moderate computer selected card 1 by default." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    return 0;
}

string ModerateComputerStrategy::toString() {
    return "Moderate Computer Strategy";
}

void ModerateComputerStrategy::takeAction(Action action, int id, vector<Territory *> &territories,
                                          int &remainingCubesRef, map<int, vector<int>> territoryAdjacencyList,
                                          int flyAbility, int &remainingCity,
                                          map<int, int*>& remainingCubesMap, map<int, int>& immuneAttackMap) {
    cout << "--------------------------------------" << endl;
    cout << "You can " << action << ". (You are player " << id << ")" << endl;
    cout << "--------------------------------------" << endl;
    if (action.actionType == ActionType::placeArmy) {
        moderatePlaceNewArmies(id, action.amount, territories, remainingCubesRef);
    } else if (action.actionType == ActionType::moveArmy) {
        moderateMoveArmies(id, action.amount, territories, territoryAdjacencyList, flyAbility);
    } else if (action.actionType == ActionType::buildCity) {
        moderateBuildCity(id, territories, remainingCity);
    } else if (action.actionType == ActionType::destroyArmy) {
        moderateDestroyArmy(id, territories, remainingCubesMap, immuneAttackMap);
    }
}

int ModerateComputerStrategy::selectOrCard(Card *card) {
    for (int i = 0; i < card->getActions().size(); ++i) {
        ActionType actionType = card->getActions()[i].actionType;
        if (actionType == ActionType::moveArmy || actionType == ActionType::placeArmy) {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "The moderate computer selected action " << i + 1 << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return i + 1;
        }
    }
    return 1;
}

void ModerateComputerStrategy::moderatePlaceNewArmies(int id, int movingPoints, vector<Territory*>& territories,
                                                  int &remainingCubesRef) {
    cout << "Game rule: You may place new armies only on the starting region or on a region where you have a city."
         << endl;
    cout << "You may place new armies in these territories: ";
    map<int, int> validTerritories; // territoryId -> the number of armies placed
    for (auto & territory : territories) {
        if (territory->getIsStartingRegion() || territory->getCities()[id] > 0) {
            cout << territory->getId() << ", ";
            validTerritories[territory->getId()] = 0;
        }
    }
    cout << endl;
    while (movingPoints > 0) {
        for (auto &[k, v] : validTerritories) {
            Territory* territory = getTerritoryById(k, territories);
            territory->placeNewArmiesOfPlayer(id, 1);
            validTerritories[k]++;
            movingPoints--;
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "The Moderate computer " << id << " places ";
    for (auto &[k, v] : validTerritories) {
        cout << v << " armies at Territory " << k << "; ";
    }
    cout << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void ModerateComputerStrategy::moderateMoveArmies(int id, int movingPoints, vector<Territory *> &territories,
                                              map<int, vector<int>> &territoryAdjacencyList, int flyAbility) {
    printNeighborsOfTerritoriesWithArmies(id, territories, territoryAdjacencyList);
    int lastMovingPoint = movingPoints;
    while (movingPoints > 0) {
        for (auto & territory : territories) {
            int numOfArmies = territory->getArmies()[id];
            if (numOfArmies > 0) {
                vector<int> neighbors = territoryAdjacencyList[territory->getId()];
                for (int neighbor : neighbors) {
                    int distance = 1;
                    Territory* neighborTerritory = getTerritoryById(neighbor, territories);
                    if (territory->getContinentId() != neighborTerritory->getContinentId()) {
                        distance = 3;
                    }
                    int cost = distance;
                    if (distance == 3) {
                        if (flyAbility == 1) {
                            cout << "\nFlying level 1! The cost to move over water is 2 per army." << endl;
                            cost = 2;
                        } else if (flyAbility >= 2) {
                            cout << "\nFlying level 2! The cost to move over water is 1 per army." << endl;
                            cost = 1;
                        }
                    }
                    if (numOfArmies > 1 && neighborTerritory->getArmies()[id] < numOfArmies && movingPoints >= cost) {
                        territory->removeArmiesOfPlayer(id, 1);
                        neighborTerritory->placeNewArmiesOfPlayer(id, 1);
                        movingPoints -= cost;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                        cout << "The Moderate computer " << id << " moved 1 army from " << territory->getId()
                             << " to " << neighborTerritory->getId() << endl;
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    }
                }
                cout << endl;
            }
        }
        if (lastMovingPoint == movingPoints) {
            break;
        }
        lastMovingPoint = movingPoints;
    }
}

void ModerateComputerStrategy::moderateBuildCity(int id, vector<Territory *> &territories, int &remainingCity) {
    if (remainingCity <= 0) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "You have no city piece in hand! Do nothing." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        return;
    }
    cout << "Game rule: You may place a city anywhere on the board where you have an army." << endl;
    vector<Territory*> myTerritoriesWithArmies;
    cout << "My Territories With Armies:" << endl;
    for (auto & territory : territories) {
        if (territory->getArmies()[id] > 0) {
            myTerritoriesWithArmies.emplace_back(territory);
            cout << "Territory" << territory->getId() << " (" << territory->getArmies()[id] << " armies), ";
        }
    }
    cout << endl;
    if (myTerritoriesWithArmies.empty()) {
        cout << "You don't have any army, so you can't build a city." << endl;
        return;
    }
    remainingCity--;
    for (auto & territory : myTerritoriesWithArmies) {
        if (!territory->getIsStartingRegion()) {
            territory->buildCity(id);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "The Moderate computer " << id << " builds a city at territory " << territory->getId() << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return;
        }
    }
    myTerritoriesWithArmies[0]->buildCity(id);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "The Moderate computer " << id << " builds a city at territory " << myTerritoriesWithArmies[0]->getId() << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void ModerateComputerStrategy::moderateDestroyArmy(int id, vector<Territory *> &territories,
                                               map<int, int *> &remainingCubesMap, map<int, int> &immuneAttackMap) {
    int playerIdToDestroy = -1;
    for (int i = 1; i <= 4; ++i) {
        if (i != id && immuneAttackMap[i] == 0) {
            for (auto & territory : territories) {
                int numOfArmies = territory->getArmiesOfPlayer(i);
                if (numOfArmies > 0) {
                    playerIdToDestroy = i;
                    *remainingCubesMap[playerIdToDestroy] += 1;
                    territory->removeArmiesOfPlayer(playerIdToDestroy, 1);
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    cout << "The Moderate computer " << id << " destroyed 1 army of player " << playerIdToDestroy
                         << " at territory " << territory->getId() << endl;
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    return;
                }
            }
        }
    }
    cout << "Other players are all immune attack or have no army to destroy. Do nothing." << endl;
}