//
// Created by jerry on 2/26/2021.
//

#include <random>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "Game.h"
#include "MapLoader.h"
#include "BidingFacility.h"

using namespace std;

const int Game::CARD_COSTS[] = {0, 1, 1, 2, 2, 3};

Game::Game() {
    COLORS = {"purple", "white", "green", "grey"};
}

Game::~Game() {

}

bool Game::start() {
    cout << "****************************" << endl;
    cout << "Eight-Minute_Empire_Legends." << endl;
    cout << "****************************" << endl;
    coinSupply = 36;
    for (const auto & color : COLORS) {
        armies[color] = 18;
        cities[color] = 3;
    }
    bool selectMapSucceed = selectMap();
    if (!selectMapSucceed) {
        return false;
    }
    selectNumberOfPlayers();
    createPlayers();
    createDeck();
    return true;
}

bool Game::startup() {
    cout << "****************************" << endl;
    cout << "     Startup phase:" << endl;
    cout << "****************************" << endl;
    cout << "\nShuffling deck..." << endl;
    deck->shuffleDeck();
    cout << "There are " << deck->getDeckVector()->size() << " cards in the deck." << endl;
    cout << "\nDrawing six cards..." << endl;
    hand = new Hand(deck); // draw six cards
    printSixCards();
    cout << "\nThere are " << deck->getDeckVector()->size() << " cards in the deck." << endl;
    cout << "\nSelecting starting region..." << endl;
    if (!selectStartingRegion()) {
        return false;
    }
    cout << "\nPlacing armies and cities on the starting region..." << endl;
    createArmiesAndCities();
    map->printForce(numOfPlayer);
    cout << "\nPlayers bidding..." << endl;
    bid();
    return true;
}

void Game::play() {
    cout << "****************************" << endl;
    cout << "     Main Game starts!" << endl;
    cout << "****************************" << endl;
    bool gameEnd = players[0]->getCards().size() == 13;
    while (!gameEnd) {
        for (int i : order) {
            cout << "It's player " << i << "'s turn:\n" << endl;
            Player* currentPlayer = getPlayerById(i);
            // TODO: 给玩家一些行动选择，比如查看地图以及其他各种信息
            printSixCards();
            selectCard(currentPlayer);
            // TODO 玩家得到good, 然后action

            // Part 5
            printSixCards();
        }
        // TODO： 暂时把回合数改成2,记得改回13
        gameEnd = players[0]->getCards().size() == 2;
        cout << "****************************" << endl;
        cout << "****************************" << endl;
    }
}

void Game::selectCard(Player* currentPlayer) {
    int cardIndex;
    while (true) {
        cout << "Please select a card index (1-6):" << endl;
        cout << ">> ";
        cin >> cardIndex;
        if (cardIndex < 1 || cardIndex > 6) {
            cout << "ERROR! Please enter a number from range 1-6!" << endl;
            cout << "Try again." << endl;
            continue;
        }
        cardIndex--;
        if (currentPlayer->getCoins() < CARD_COSTS[cardIndex]) {
            cout << "ERROR! You don't have enough coin to buy this card!" << endl;
            cout << "Try again." << endl;
            continue;
        }
        break;
    }
    currentPlayer->PayCoin(CARD_COSTS[cardIndex]);
    currentPlayer->exchange((*hand->getHandVector())[cardIndex]);
    hand->exchange(cardIndex + 1, deck);
}

void Game::computeScore() {
    // TODO
}

bool Game::selectMap() {
    string filePath;
    string path = "../Maps/";
    vector<string> mapFiles;
    for (const auto & entry : std::filesystem::directory_iterator(path)){
        mapFiles.push_back(entry.path().string().erase(entry.path().string().find(path), path.size()));
    }
    int filePathOption = -1;
    //Map selection
    while (true) {
        try {
            cout << "Please chose your game map"<< endl;
            for(int i = 0; i < mapFiles.size(); i++) {
                cout << i + 1 << ". " << mapFiles[i] << endl;
            }
            cout << mapFiles.size() + 1 << ". Exit" << endl;
            cout << ">> ";
            cin >> filePathOption;
            if (filePathOption < 1 || filePathOption > (mapFiles.size() + 1)) {
                throw out_of_range("Unknown option, please chose again!");
            } else if (filePathOption == mapFiles.size() + 1) {
                cout << "GOODBYE" << endl;
                return false;
            }
            filePath = path + mapFiles[filePathOption - 1];
            map = MapLoader::loadMap(filePath);
            cout << *map << endl;
            cout << "The map is created successfully!\n" << endl;
            break;
        } catch (out_of_range& e) {
            cout << e.what() << endl;
        }
    }
    return true;
}

void Game::selectNumberOfPlayers() {
    int numberOfPlayers;
    cout << "Please select the number of players: (2, 3, 4)" << endl;
    cout << ">> ";
    cin >> numberOfPlayers;
    this->numOfPlayer = numberOfPlayers;
}

void Game::createPlayers() {
    int coins;
    if (numOfPlayer == 4) {
        coins = 9;
    } else if (numOfPlayer == 3) {
        coins = 11;
    } else if (numOfPlayer == 2) {
        coins = 14;
    }
    string name;
    string firstName;
    string lastName;
    string color;
    int bidding;
    vector<string> remainingColors = COLORS;
    for (int i = 0; i < numOfPlayer; ++i) {
        cout << "Please enter the full name of player " << i + 1 << ": (separate by space)" << endl;
        cout << ">> ";
        cin >> firstName;
        cin >> lastName;
        while (true) {
            cout << "Please enter the color of player " << i + 1 << ": (";
            for (int j = 0; j < remainingColors.size(); ++j) {
                cout << remainingColors[j];
                if (j != remainingColors.size() - 1) {
                    cout << ", ";
                } else {
                    cout << ")\n>> ";
                }
            }
            cin >> color;
            auto itr = find(remainingColors.begin(), remainingColors.end(), color);
            if (itr != remainingColors.end()) {
                remainingColors.erase(itr);
                break;
            } else {
                cout << "ERROR! Please type a correct color name." << endl;
            }
        }
        cout << "Please enter the bidding of player " << i + 1 << ":" << endl;
        cout << ">> ";
        cin >> bidding;
        coinSupply -= coins;
        cities[color] -= 3;
        armies[color] -= 18;
        players.emplace_back(new Player(i + 1, firstName, lastName, color, bidding, coins));
        cout << *players[i];
        cout << "Player " << i + 1 << " is created successfully!\n" << endl;
    }
}

void Game::createDeck() {
    deck = new Deck(numOfPlayer);
}

void Game::createArmiesAndCities() {
    Territory* startingTerritory = map->getTerritoryById(startRegionId);
    for (auto player : players) {
        player->PlaceNewArmies(4, startingTerritory);
    }
    if (numOfPlayer == 2) {
        vector<string> remainingColors = COLORS;
        for (auto & player : players) {
            auto itr = find(remainingColors.begin(), remainingColors.end(), player->getColor());
            remainingColors.erase(itr);
        }
        string nonPlayerColor = remainingColors[0];
        int numOfTerritories = map->getTerritories().size();
        int territoryId = -1;
        for (int i = 0; i < 10; i++) {
            cout << "Player " << players[i % 2]->getId() << ", please select a territory from 1-" << numOfTerritories
                 << endl;
            cin >> territoryId;
            if (territoryId < 1 || territoryId > numOfTerritories) {
                cout << "Invalid territory ID! Please try again." << endl;
                i--;
                cin.clear();
                cin.ignore();
            } else {
                //Assume non-player army has playerId of 0
                map->getTerritoryById(territoryId)->placeNewArmiesOfPlayer(0, 1);
                armies[nonPlayerColor]--;
            }
        }
    }
    for (auto player : players) {
        cout << *player;
    }
}

void Game::printSixCards() {
    cout << "The six cards:" << endl;
    cout << "Index:";
    for (int i = 1; i <= 6; ++i) {
        cout << setw(17) <<  to_string(i) + "        ";
    }
    cout << "\nCost: ";
    for (int cost : CARD_COSTS) {
        cout << setw(17) <<  to_string(cost) + "        ";
    }
    cout << endl;
    cout << "Card: ";
    for (auto & card : *hand->getHandVector()) {
        cout << setw(17) << card->getName();
    }
    cout << "\n" << endl;
}

bool Game::criteriaA(int regionId) {
    vector<int> neighbors = map->getTerritoryNeighborsById(regionId);
    for (int neighbor : neighbors) {
        if (map->getDistance(regionId, neighbor) == 3) {
            return true;
        }
    }
    return false;
}

bool Game::criteriaB(int regionId) {
    vector<int> neighbors = map->getTerritoryNeighborsById(regionId);
    int waterConnectionCount = 0;
    for (int neighbor : neighbors) {
        if (map->getDistance(regionId, neighbor) == 1 && criteriaA(neighbor)) {
            return true;
        }
        if (map->getDistance(regionId, neighbor) == 3) {
            waterConnectionCount++;
        }
    }
    if (waterConnectionCount >= 2) {
        return true;
    }
    return false;
}

bool Game::selectStartingRegion() {
    vector<Territory*> tempRegions = map->getTerritories();
    shuffle(tempRegions.begin(), tempRegions.end(), std::mt19937(std::random_device()()));
    cout << "Shuffling region IDs..." << endl;
    for (auto & tempRegion : tempRegions) {
        cout << tempRegion->getId() << " ";
    }
    for (auto & tempRegion : tempRegions) {
        int regionId = tempRegion->getId();
        if (criteriaA(regionId) && criteriaB(regionId)) {
            startRegionId = regionId;
            cout << "\n\nStart region is " << startRegionId << "!\n" << endl;
            return true;
        }
    }
    cout << "There is no qualified region! Exit." << endl;
    return false;
}

void Game::bid() {
    int winnerID = BidingFacility::bid(players);
    cout << "The bidding winner is player " << winnerID << "!\n" << endl;
    Player* winner = getPlayerById(winnerID);
    winner->PayCoin(winner->getBiding());
    order.emplace_back(winnerID);
    vector<int> otherPlayerIDs;
    for (auto & player : players) {
        if (player->getId() != winnerID) {
            otherPlayerIDs.emplace_back(player->getId());
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(otherPlayerIDs.begin(), otherPlayerIDs.end(), g);
    for (auto & otherPlayerID : otherPlayerIDs) {
        order.emplace_back(otherPlayerID);
    }
    cout << "The order of players' move is:" << endl;
    for (int i : order) {
        cout << i << " ";
    }
    cout << "\n\n";
}

Player* Game::getPlayerById(int id) {
    for (auto & player : players) {
        if (player->getId() == id) {
            return player;
        }
    }
    cout << "ERROR! No player has this id.";
    return nullptr;
}



