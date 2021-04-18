//
// Created by Jingchao Zhang on 2/26/2021.
//

#include <random>
#include <sstream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "GameEngine.h"
#include "MapLoader.h"
#include "BidingFacility.h"

using namespace std;

GameEngine::GameEngine() {
    COLORS = {"purple", "white", "green", "grey"};
    gameEnd = false;
}

GameEngine::~GameEngine() {
    if (hand != nullptr) {
        delete hand;
        hand = nullptr;
    }
    if (deck != nullptr) {
        delete deck;
        deck = nullptr;
    }
    if (map != nullptr) {
        delete map;
        map = nullptr;
    }
    for (auto & player : players) {
        delete player;
        player = nullptr;
    }
}

bool GameEngine::start() {
    cout << "****************************" << endl;
    cout << "Eight-Minute_Empire_Legends." << endl;
    cout << "****************************" << endl;

    cout << "Creating game components...\n" << endl;
    coinSupply = 36;
    for (const auto & color : COLORS) {
        armies[color] = 18;
        cities[color] = 3;
    }
    printComponents();
    bool selectMapSucceed = selectMap();
    if (!selectMapSucceed) {
        return false;
    }
    selectMode();
    selectNumberOfPlayers();
    createPlayers();
    cout << "Creating a deck of cards..." << endl;
    createDeck();
    cout << "A deck of cards are created! There are " << deck->getCards().size() << " cards in the deck.\n" << endl;
    printComponents();
    return true;
}

bool GameEngine::startup() {
    cout << "****************************" << endl;
    cout << "     Startup phase:" << endl;
    cout << "****************************" << endl;
    cout << "\nShuffling deck..." << endl;
    deck->shuffleDeck();
    cout << "There are " << deck->getCards().size() << " cards in the deck." << endl;
    cout << "\nDrawing six cards..." << endl;
    hand = new Hand(deck); // draw six cards
    cout << *hand;
    cout << "There are " << deck->getCards().size() << " cards in the deck." << endl;
    cout << "\nSelecting starting region..." << endl;
    if (!selectStartingRegion()) {
        return false;
    }
    cout << "\nPlacing armies and cities on the starting region..." << endl;
    createArmiesAndCities();
    map->printForce(numOfPlayer);
    cout << "\nPlayers bidding..." << endl;
    bidAndDecideMovingOrder();
    return true;
}

void GameEngine::play() {
    cout << "****************************" << endl;
    cout << "     Main Game starts!" << endl;
    cout << "****************************" << endl;
    int roundNumber = 1;
    while (roundNumber <= maxRound) {
        for (int i = 0; i < order.size(); ++i) {
            int currentPlayerId = order[i];
            cout << "It's player " << currentPlayerId << "'s turn:\n" << endl;
            currentPlayer = getPlayerById(currentPlayerId);
            if (!tournamentMode) {
                changeStrategyPrompt(currentPlayer);
            }
            cout << *hand;
            currentPlayer->printMyAbilities();
            Card* card = currentPlayer->selectCard(hand, deck);
            cardIndex = currentPlayer->cardIndex;
            if (card->getAnd() || card->getOr()) {
                currentPlayer->AndOrAction(card);
            } else {
                currentPlayer->takeAction(card->getActions()[0]);
            }
            if (roundNumber == maxRound && i == order.size() - 1) {
                gameEnd = true;
            }
            Notify();
            if (!gameEnd && !tournamentMode) {
                cout << "Player " << currentPlayer->getId()
                     << ", your turn is completed! Press Enter to pass to other players..." << endl;
                cin.ignore(10, '\n');
                cin.get();
                cout << "********************************************" << endl;
                cout << "********************************************" << endl;
            }
        }
        roundNumber++;
    }
}

void GameEngine::computeScore() {
    computeMapScore();
    computeAbilityScore();
    computeElixirScore();
}

void GameEngine::computeMapScore() {
    // Territory
    cout << "Computing Territory scores..." << endl;
    for (auto & territory : map->getTerritories()) {
        int playerId = territory->getControllingPlayerId();
        if (playerId > 0) {
            cout << "Player " << playerId << " is controlling territory " << territory->getId() << endl;
            Player* player = getPlayerById(playerId);
            player->addScore(1);
        }
    }
    // Continent
    cout << "\nComputing Continent scores..." << endl;
    for(auto continent: map->getContinents()){
        int playerId = continent->getControllingPlayerId();
        if (playerId > 0) {
            cout << "Player " << playerId << " is controlling continent " << continent->getId() << endl;
            Player* player = getPlayerById(playerId);
            player->addScore(1);
        }
    }
    cout << endl;
}

void GameEngine::computeAbilityScore() {
    cout << "Computing Ability scores..." << endl;
    for (auto & player : players) {
        for (auto type : player->getCardTypeVp()) {
            cout << "Player " << player->getId() << " gains 1 VP from each " << Card::cardTypeToString(type) << endl;
            player->addScore(player->getNumberOfCardsOfEachType()[type]);
        }
        for (auto type : player->getCardSetVp()) {
            if (type == noble && player->getNumberOfCardsOfEachType()[noble] == 3) {
                cout << "Player " << player->getId() << " gains 4 VP from three noble cards." << endl;
                player->addScore(4);
            } else if (type == mountain && player->getNumberOfCardsOfEachType()[mountain] == 2) {
                cout << "Player " << player->getId() << " gains 3 VP from two mountain cards." << endl;
                player->addScore(3);
            }
        }
        if (player->hasOneVpPer3Coins()) {
            cout << "Player " << player->getId() << " gains " << player->getCoins() / 3 << " VP from coins left." << endl;
            player->addScore(player->getCoins() / 3);
        }
        if (player->hasOneVpPerFlying()) {
            int flyingVP = player->getAbilities()[AbilityType::flying];
            cout << "Player " << player->getId() << " gains " << flyingVP << " VP from flying." << endl;
            player->addScore(flyingVP);
        }
    }
}

void GameEngine::computeElixirScore() {
    vector<Player*> hasMostElixirs;
    int highest = -1;
    for (auto & player : players) {
        int numberOfElixir = player->getAbilities()[AbilityType::elixir];
        if (numberOfElixir > highest) {
            highest = numberOfElixir;
            hasMostElixirs.clear();
            hasMostElixirs.emplace_back(player);
        } else if (numberOfElixir == highest) {
            hasMostElixirs.emplace_back(player);
        }
    }
    if (hasMostElixirs.size() == 1) {
        cout << "Player " << hasMostElixirs[0]->getId() << " gains 2 VP from Elixirs." << endl;
        hasMostElixirs[0]->addScore(2);
    } else {
        for (auto & player : hasMostElixirs) {
            cout << "Player " << player->getId() << " gains 1 VP from Elixirs." << endl;
            player->addScore(1);
        }
    }
}

void GameEngine::claimWinner() {
    cout << endl;
    for (auto & player : players) {
        int armiesOnBoard = 0;
        for (auto & territory : map->getTerritories()) {
            armiesOnBoard += territory->getArmies()[player->getId()];
        }
        int numOfControlledRegions = 0;
        for (auto & territory : map->getTerritories()) {
            if (territory->getControllingPlayerId() == player->getId()) {
                numOfControlledRegions++;
            }
        }
        cout << "Player " << player->getId() << ":   score: " << player->getScore() << ", coins: " << player->getCoins()
        << ", armies: " << armiesOnBoard << ", controlled regions: " << numOfControlledRegions << endl;
    }
    vector<Player*> playersWithHighestScore;
    int highestScore = -1;
    for (auto & player : players) {
        if (player->getScore() > highestScore) {
            highestScore = player->getScore();
            playersWithHighestScore.clear();
            playersWithHighestScore.emplace_back(player);
        } else if (player->getScore() == highestScore) {
            playersWithHighestScore.emplace_back(player);
        }
    }
    if (playersWithHighestScore.size() == 1) {
        displayWinner(playersWithHighestScore[0]);
        return;
    }

    vector<Player*> playersWithMostCoins;
    int mostCoins = -1;
    for (auto & player : playersWithHighestScore) {
        if (player->getCoins() > mostCoins) {
            mostCoins = player->getCoins();
            playersWithMostCoins.clear();
            playersWithMostCoins.emplace_back(player);
        } else if (player->getCoins() == mostCoins) {
            playersWithMostCoins.emplace_back(player);
        }
    }
    if (playersWithMostCoins.size() == 1) {
        displayWinner(playersWithMostCoins[0]);
        return;
    }

    vector<Player*> playersWithMostArmies;
    int mostArmies = -1;
    for (auto & player : playersWithMostCoins) {
        int armiesOnBoard = 0;
        for (auto & territory : map->getTerritories()) {
            armiesOnBoard += territory->getArmies()[player->getId()];
        }
        if (armiesOnBoard > mostArmies) {
            mostArmies = armiesOnBoard;
            playersWithMostArmies.clear();
            playersWithMostArmies.emplace_back(player);
        } else if (armiesOnBoard == mostArmies) {
            playersWithMostArmies.emplace_back(player);
        }
    }
    if (playersWithMostArmies.size() == 1) {
        displayWinner(playersWithMostArmies[0]);
        return;
    }

    vector<Player*> playersWithMostControlledRegions;
    int mostControlledRegions = -1;
    for (auto & player : playersWithMostArmies) {
        int numOfControlledRegions = 0;
        for (auto & territory : map->getTerritories()) {
            if (territory->getControllingPlayerId() == player->getId()) {
                numOfControlledRegions++;
            }
        }
        if (numOfControlledRegions > mostControlledRegions) {
            mostControlledRegions = numOfControlledRegions;
            playersWithMostControlledRegions.clear();
            playersWithMostControlledRegions.emplace_back(player);
        } else if (numOfControlledRegions == mostControlledRegions) {
            playersWithMostControlledRegions.emplace_back(player);
        }
    }
    if (playersWithMostControlledRegions.size() == 1) {
        displayWinner(playersWithMostControlledRegions[0]);
        return;
    }
    cout << "********************************************"  << endl;
    cout << "                Draw! " << endl;
    cout << "********************************************"  << endl;
}

void GameEngine::displayWinner(Player *player) {
    cout << "********************************************"  << endl;
    cout << "     WINNER is player " << player->getId() << ": " << player->getFirstName() << " " << player->getLastName()
            << "!" << endl;
    cout << "         CONGRATULATIONS!!!" << endl;
    cout << "********************************************"  << endl;
}

bool GameEngine::selectMap() {
    string filePath;
    string path = "Maps/";
    vector<string> mapFiles = {"Disconnected.map", "GAME1_invalid.map", "Lshape.map", "Rectangular.map"};

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

            bool validateResult = map->validate();
            if (!validateResult) {
                throw logic_error("This is not a valid map! Please choose another one.");
            }
            cout << *map << endl;
            cout << "The map is created successfully!\n" << endl;
            break;
        } catch (out_of_range& e) {
            cout << e.what() << endl;
        } catch (const std::string e) {
            cout << e << endl;
        } catch (logic_error& e) {
            cout << e.what() << endl;
        }
    }
    return true;
}

void GameEngine::selectNumberOfPlayers() {
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
    switch (numOfPlayer) {
        case 2:
            maxRound = 13;
            break;
        case 3:
            maxRound = 10;
            break;
        case 4:
            maxRound = 8;
            break;
    }
}

void GameEngine::createPlayers() {
    int coins = initCoinsForEachPlayer();
    vector<string> remainingColors = COLORS;
    for (int i = 0; i < numOfPlayer; ++i) {
        string firstName;
        string lastName;
        cout << "Please enter the full name of player " << i + 1 << ": (separate by space)" << endl;
        cout << ">> ";
        cin >> firstName;
        cin >> lastName;
        string color = selectColor(i + 1, remainingColors);
        auto itr = find(remainingColors.begin(), remainingColors.end(), color);
        remainingColors.erase(itr);
        int bidding = selectBidding(i + 1, coins);
        PlayerStrategy *initPlayerStrategy = selectStrategy();
        coinSupply -= coins;
        cities[color] -= 3;
        armies[color] -= 18;
        players.emplace_back(new Player(i + 1, firstName, lastName, color, bidding, coins,
                                        map->getTerritories(), initPlayerStrategy));
        cout << *players[i];
        cout << "Player " << i + 1 << " is created successfully!\n" << endl;
    }
    for (auto & player : players) {
        player->setPlayers(players);
        player->setTerritoryAdjacencyList(map->getTerritoryAdjacencyList());
    }
}

void GameEngine::createDeck() {
    deck = new Deck(numOfPlayer);
}

void GameEngine::createArmiesAndCities() {
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

bool GameEngine::criteriaA(int regionId) {
    vector<int> neighbors = map->getTerritoryNeighborsById(regionId);
    for (int neighbor : neighbors) {
        if (map->getDistance(regionId, neighbor) == 3) {
            return true;
        }
    }
    return false;
}

bool GameEngine::criteriaB(int regionId) {
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

bool GameEngine::selectStartingRegion() {
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

void GameEngine::bidAndDecideMovingOrder() {
    int winnerID = BidingFacility::bid(players);
    cout << "The bidding winner is player " << winnerID << "!\n" << endl;
    Player* winner = getPlayerById(winnerID);
    winner->PayCoin(winner->getBiding());
    coinSupply += winner->getBiding();
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

Player* GameEngine::getPlayerById(int id) {
    for (auto & player : players) {
        if (player->getId() == id) {
            return player;
        }
    }
    cout << "ERROR! No player has this id.";
    return nullptr;
}

void GameEngine::printComponents() {
    cout << "Game components..." << endl;
    cout << "Coins: " << coinSupply << endl;
    cout << "Armies: ";
    for (int i = 0; i < COLORS.size(); ++i) {
        cout << armies[COLORS[i]] << " " << COLORS[i];
        if (i != COLORS.size() - 1) {
            cout << ", ";
        }
    }
    cout << "\nCities: ";
    for (int i = 0; i < COLORS.size(); ++i) {
        cout << cities[COLORS[i]] << " " << COLORS[i];
        if (i != COLORS.size() - 1) {
            cout << ", ";
        }
    }
    cout << "\n\n";
}

PlayerStrategy* GameEngine::selectStrategy() {
    int strategy;
    cout << "Please select a strategy:" << endl;
    if (tournamentMode) {
        cout << "1. Greedy computer" << endl;
        cout << "2. Moderate computer" << endl;
        cout << ">>";
        cin >> strategy;
        while (strategy < 1 || strategy > 2) {
            cout << "ERROR! Please select a number from 1 to 2. Try again." << endl;
            cin >> strategy;
        }
        PlayerStrategy *initPlayerStrategy;
        switch (strategy) {
            case 1:
                initPlayerStrategy = new GreedyComputerStrategy();
                break;
            case 2:
                initPlayerStrategy = new ModerateComputerStrategy();
                break;
            default:
                initPlayerStrategy = new GreedyComputerStrategy();
        }
        return initPlayerStrategy;
    }
    cout << "1. Human player" << endl;
    cout << "2. Greedy computer" << endl;
    cout << "3. Moderate computer" << endl;
    cout << ">>";
    cin >> strategy;
    while (strategy < 1 || strategy > 3) {
        cout << "ERROR! Please select a number from 1 to 3!" << endl;
        cin >> strategy;
    }
    PlayerStrategy *initPlayerStrategy;
    switch (strategy) {
        case 1:
            initPlayerStrategy = new HumanStrategy();
            break;
        case 2:
            initPlayerStrategy = new GreedyComputerStrategy();
            break;
        case 3:
            initPlayerStrategy = new ModerateComputerStrategy();
            break;
        default:
            initPlayerStrategy = new HumanStrategy();
    }
    return initPlayerStrategy;
}

int GameEngine::selectBidding(int playerId, int coins) {
    int bidding;
    cout << "Please enter the bidding of player " << playerId << ": (0-" << coins << ")" << endl;
    cout << "(The coins will be deducted only if you win the bidding later.)" << endl;
    cout << ">> ";
    cin >> bidding;
    while (bidding < 0 || bidding > coins) {
        cout << "ERROR! Please enter the bidding of player " << playerId << ": (0-" << coins << ")" << endl;
        cout << ">> ";
        cin >> bidding;
    }
    return bidding;
}

int GameEngine::initCoinsForEachPlayer() {
    if (numOfPlayer == 4) {
        return 9;
    } else if (numOfPlayer == 3) {
        return 11;
    } else if (numOfPlayer == 2) {
        return 14;
    }
    return 0;
}

string GameEngine::selectColor(int playerId, vector<string> remainingColors) {
    string color;
    while (true) {
        cout << "Please enter the color of player " << playerId << ": (";
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
            break;
        } else {
            cout << "ERROR! Please type a correct color name." << endl;
        }
    }
    return color;
}

void GameEngine::changeStrategyPrompt(Player *currentPlayer) {
    cout << "The current strategy of this player is " << currentPlayer->getStrategy() << endl;
    cout << "Do you want to change strategy? (Yes or No)" << endl;
    string ans;
    cin >> ans;
    while (ans != "Yes" && ans != "No") {
        cout << R"(Please type "Yes" or "No".)" << endl;
        cin >> ans;
    }
    if (ans == "No") {
        return;
    }
    PlayerStrategy* newStrategy = selectStrategy();
    currentPlayer->setStrategy(newStrategy);
}

Player *GameEngine::getCurrentPlayer() {
    return currentPlayer;
}

int GameEngine::getCardIndex() {
    return cardIndex;
}

Map *GameEngine::getMap() {
    return map;
}

int GameEngine::getNumOfPlayers() {
    return numOfPlayer;
}

bool GameEngine::isGameEnd() {
    return gameEnd;
}

void GameEngine::selectMode() {
    int option;
    cout << "Please choose one game mode: " << endl;
    cout << "1. Single game mode" << endl;
    cout << "2. Tournament mode" << endl;
    cout << ">>";
    cin >> option;
    while (option < 1 || option > 2) {
        cout << "Invalid number! Please enter 1 or 2." << endl;
        cout << ">>";
        cin >> option;
    }
    if (option == 2) {
        tournamentMode = true;
    } else {
        tournamentMode = false;
    }
}



