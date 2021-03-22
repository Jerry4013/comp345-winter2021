//
// Created by Jingchao Zhang on 2/26/2021.
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
    cout << "There are " << deck->getCards().size() << " cards in the deck." << endl;
    cout << "\nDrawing six cards..." << endl;
    hand = new Hand(deck); // draw six cards
    printSixCards();
    cout << "\nThere are " << deck->getCards().size() << " cards in the deck." << endl;
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
            // TODO 提示玩家在行动之前查看相关信息，进入方法后就无法查看了。
            printSixCards();
            Card* card = selectCard(currentPlayer);
            if (card->getAnd() || card->getOr()) {
                currentPlayer->AndOrAction(card);
            } else {
                currentPlayer->takeAction(card->getActions()[0]);
            }
            map->printForce(numOfPlayer);
            cout << "****************************" << endl;
            cout << "****************************" << endl;
        }
        // TODO 为测试改为3回合结束游戏，将来要改回13。
        gameEnd = players[0]->getCards().size() == 3;
    }
}

Card* Game::selectCard(Player* currentPlayer) {
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
    Card* card = hand->getHandCards()[cardIndex];
    currentPlayer->exchange(card);
    hand->exchange(cardIndex + 1, deck);
    return card;
}

void Game::computeScore() {
    // TODO compute lands score

    cout << "****************************"  << endl;
    cout << "        Game Ended"            << endl;
    cout << "****************************"  << endl;
    cout << endl;

    int winnerID;

    bool scoreTied = false;
    bool coinTied = false;
    bool armyTied = false;

    std::map<int, int> playerScores;

    // Territory
    for (auto & territory : map->getTerritories()) {
        int playerId = territory->getControllingPlayerId();
        playerScores[playerId]++;
    }


    // Continent
    for(auto continent: map->getContinents()){
        int playerId = continent->getControllingPlayerId();
        playerScores[playerId]++;
    }

    // Card
    unordered_map<int, int> playerElixirMap;
    for (auto & player : players) {
        //for one player, get the cards vector
        vector<Card *> cards = player->getCards();
        //初始总分为0 init score=0
        int totalScoreForCards = 0;
        //首先计算集合中各类卡牌的数量，初始为0 count different cards
        int nightNum = 0;
        int cursedNum = 0;
        int arcaneNum = 0;
        int ancientNum = 0;
        int direNum = 0;
        int forestNum = 0;
        int nobleNum = 0;
        int mountainNum = 0;
        int wings = 0;
        int playerElixir = 0;
        //这个for就是为了计算各类卡牌各有多少张
        for (auto &card : cards) {
            if (card->getType() == night) {
                nightNum++;
            }
            if (card->getType() == cursed) {
                cursedNum++;
            }
            if (card->getType() == arcane) {
                arcaneNum++;
            }
            if (card->getType() == ancient) {
                ancientNum++;
            }
            if (card->getType() == dire) {
                direNum++;
            }
            if (card->getType() == forest) {
                forestNum++;
            }
            if (card->getType() == noble) {
                nobleNum++;
            }
            if (card->getType() == mountain) {
                mountainNum++;
            }
            if (card->getAbilities().at(0).abilityType == flying) {
                wings++;
            }
            if (card->getAbilities().at(0).abilityType == elixir) {
                playerElixir = playerElixir + card->getAbilities().at(0).amount;
            }
        }
        playerElixirMap[player->getId()]=playerElixir;
        //count scores
        for (auto &card : cards) {
            //功能1：玩家最后剩下钱，剩下3块给1分，每剩3块1分，比如剩下6块钱给两分
            //coinsLeft
            if (card->getAbilities()[0].vpType == coinsLeft) {
                int money = player->getCoins();
                int score = money / 3;
                totalScoreForCards = totalScoreForCards + score;
            }
            //功能2-7：每有一张Ancient给1分。功能3-8是不同的类别。这里放在一个loop里不会重复计算的原因是，所有加分的功能的牌都只有一张，不会出现第二张一样的牌。
            if (card->getAbilities().at(0).cardTypeForVP == ancient) {
                totalScoreForCards = totalScoreForCards + ancientNum;
            }
            if (card->getAbilities().at(0).cardTypeForVP == arcane) {
                totalScoreForCards = totalScoreForCards + arcaneNum;
            }
            if (card->getAbilities().at(0).cardTypeForVP == cursed) {
                totalScoreForCards = totalScoreForCards + cursedNum;
            }
            if (card->getAbilities().at(0).cardTypeForVP == dire) {
                totalScoreForCards = totalScoreForCards + direNum;
            }
            if (card->getAbilities().at(0).cardTypeForVP == forest) {
                totalScoreForCards = totalScoreForCards + forestNum;
            }
            if (card->getAbilities().at(0).cardTypeForVP == night) {
                totalScoreForCards = totalScoreForCards + nightNum;
            }
            //功能8：每有一张翅膀给1分。这里放在一个loop里不会重复计算的原因是，所有加分的功能的牌都只有一张，不会出现第二张一样的牌。就是只有一张One Vp per Fly
            if (card->getAbilities().at(0).vpType == vpPerFlying) {
                totalScoreForCards = totalScoreForCards + wings;
            }
            //功能9：如果有4张Noble，多给3分。只有一次3分。因为没有1 vp per noble，所以无需判断条件
            if (card->getAbilities().at(0).cardTypeForVP == noble) {
                if (nobleNum >= 4) {
                    totalScoreForCards = totalScoreForCards + 3;
                }
            }
            //功能10：如果有2张Mountain，多给3分。只有一次3分。
            if (card->getAbilities().at(0).cardTypeForVP == mountain) {
                if (mountainNum >= 2) {
                    totalScoreForCards = totalScoreForCards + 3;
                }
            }
        }
        //add cards socre for current player
        player->setScore((player->getScore())+totalScoreForCards);
    }
    int playerID = -1;
    int maxElixir = -1;
    //find the one who has most elixirs and add 2 points
    unordered_map<int, int>::iterator iter;
    for(iter = playerElixirMap.begin(); iter != playerElixirMap.end(); iter++) {
        int temp=iter->second;
        if (temp > maxElixir) {
            maxElixir=temp;
            playerID=iter->first;
        }
    }
    for (auto & player : players) {
        if (player->getId() == playerID){
            player->setScore((player->getScore()) + 2);

        }
    }

    if(playerScores.find(0) == playerScores.find(1)) scoreTied = true;
    else winnerID = claimWinner(playerScores);

    // if scores are tied, the player with the most coins wins.
    if(scoreTied){
        std::map<int, int> coinList;

        for (auto player : players)
            coinList[player->getId()] += player->getCoins();

        if(coinList.find(0) == coinList.find(1)) coinTied = true;
        else winnerID = claimWinner(coinList);
    }

    // if coins are tied, the player with the most armies wins.
    if(coinTied){
        std::map<int, int> armyList;

        for (auto player : players)
            armyList[player->getId()] += player->getRemainingCubes();

        if(armyList.find(0) == armyList.find(1)) armyTied = true;
        else winnerID = claimWinner(armyList);
    }

    // if armies are tie, the player with the most controlled regions wins
    if(armyTied){
        std::map<int, int> regList;

        for(auto territory: map->getTerritories()){
            regList[territory->getControllingPlayerId()]++;
        }

        if(regList.find(0) == regList.find(1)) cout << "TIE!" << endl;
        else winnerID = claimWinner(regList);
    }

    for(Player *player : players){
        if(player->getId() == winnerID){
            cout << "****************************"  << endl;
            cout << "       WINNER is " << player->getFirstName() << " " << player->getLastName() << endl;
            cout << "****************************"  << endl;
            cout << endl;
        }
    }

}

int Game::claimWinner(std::map<int, int> map1) {
    int max = 0;
    for (auto const& [key, val] : map1) {
        if(val>max) max = val;
    }
    return map1.at(max);
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
    while (true) {
        cout << "Please select the number of players: (2, 3, 4)" << endl;
        cout << ">> ";
        cin >> numberOfPlayers;
        if (numberOfPlayers < 2 || numberOfPlayers > 4) {
            cout << "Error! Please select a valid number." << endl;
        } else {
            break;
        }
    }
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
        cout << "Please enter the bidding of player " << i + 1 << ": (0-" << coins << ")" << endl;
        cout << "(The coins will be deducted only if you win the bidding later.)" << endl;
        cout << ">> ";
        cin >> bidding;
        coinSupply -= coins;
        cities[color] -= 3;
        armies[color] -= 18;
        players.emplace_back(new Player(i + 1, firstName, lastName, color, bidding, coins,
                                        map->getTerritories()));
        cout << *players[i];
        cout << "Player " << i + 1 << " is created successfully!\n" << endl;
    }
    for (auto & player : players) {
        player->setPlayers(players);
        player->setTerritoryAdjacencyList(map->getTerritoryAdjacencyList());
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
    for (auto & card : hand->getHandCards()) {
        cout << setw(17) << card->getName();
    }
    cout << "\n" << endl;
    cout << "Card: ";
    for (auto & card : hand->getHandCards()) {
        cout << *card << endl;
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
            tempRegion->setIsStartingRegion(true);
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



