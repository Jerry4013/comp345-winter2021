//
// Created by jerry on 2/26/2021.
//

#include <sstream>
#include <filesystem>
#include <algorithm>
#include <random>
#include <string>
#include <iomanip>
#include "Game.h"
#include "MapLoader.h"
#include "BidingFacility.h"

using namespace std;

const vector<int> Game::CARD_COSTS = {0, 1, 1, 2, 2, 3};
const vector<string> Game::COLORS = {"purple", "white", "green", "grey"};

Game::Game() {
}

Game::~Game() {

}

bool Game::start() {
    cout << "****************************" << endl;
    cout << "Eight-Minute_Empire_Legends." << endl;
    cout << "****************************" << endl;
    bool selectMapSucceed = selectMap();
    if (!selectMapSucceed) {
        return false;
    }
    selectNumberOfPlayers();
    createPlayers();
    createDeck();
    coinSupply = 36;
    for (const auto & color : COLORS) {
        armies[color] = 18;
        cities[color] = 3;
    }
    return true;
}

void Game::startup() {
    //Shuffling the cards: the deck is already shuffled when creating.
    hand = new Hand(deck); // draw six cards
    printSixCards();
    createArmiesAndCities();
    bid();
}

void Game::play() {
    cout << "****************************" << endl;
    cout << "     Main Game starts!" << endl;
    cout << "****************************" << endl;
    bool gameEnd = players[0]->getCards().size() == 13;
    while (!gameEnd) {
        for (int i : order) {
            cout << "It's player " << i << "'s turn:" << endl;
            Player* currentPlayer = getPlayerById(i);
        }

        gameEnd = players[0]->getCards().size() == 13;
        gameEnd = true;
    }
}

void Game::computeScore() {

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
        try{
            cout << "Please chose your game map"<< endl;
            for(int i = 0; i < mapFiles.size(); i++) {
                cout << i + 1 << ". " << mapFiles[i] << endl;
            }
            cout << mapFiles.size() + 1 << ". Exit" << endl;
            cout << ">>";
            cin >> filePathOption;
            if(filePathOption < 1 || filePathOption > (mapFiles.size() + 1)) {
                throw string("Unknown option, please chose again!");
            } else if (filePathOption == mapFiles.size() + 1) {
                cout << "GOODBYE" << endl;
                return false;
            }
            filePath = path + mapFiles[filePathOption - 1];
            map = MapLoader::loadMap(filePath);
            cout << *map << endl;
            cout << "The map is created successfully!\n" << endl;
            break;
        } catch (const std::string e) {
            cout << e << endl;
        }
    }
    return true;
}

void Game::selectNumberOfPlayers() {
    int numberOfPlayers;
    cout << "Please select the number of players: (2, 3, 4)" << endl;
    cout << ">>";
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
    for (int i = 0; i < numOfPlayer; ++i) {
        cout << "Please enter the first name of player " << i + 1 << ":" << endl;
        cout << ">>";
        cin >> firstName;
        cout << "Please enter the last name of player " << i + 1 << ":" << endl;
        cout << ">>";
        cin >> lastName;
        cout << "Please enter the color of player " << i + 1 << ": (purple, white, green, grey) " << endl;
        cout << ">>";
        cin >> color;
        cout << "Please enter the bidding of player " << i + 1 << ":" << endl;
        cout << ">>";
        cin >> bidding;
        coinSupply -= coins;
        players.emplace_back(new Player(i + 1, firstName, lastName, color, bidding, coins));
        cout << *players[i];
        cout << "Player " << i + 1 << " is created successfully!\n" << endl;
    }
}

void Game::createDeck() {
    deck = new Deck(numOfPlayer);
    // TODO: deckVector最好能改成不是指针
}

void Game::createArmiesAndCities() {
    int startingRegion = selectStartingRegion();

    // TODO: 在Map和Player里都需要初始化军队 (Part 2, 第2)
    // TODO：根据游戏规则，如果是两个玩家，需要有nonPlayerArmy
    // TODO: 最后要print player
}

void Game::printSixCards() {
    cout << "The six cards:" << endl;
    cout << "Cost:";
    for (int cost : CARD_COSTS) {
        cout << setw(17) <<  to_string(cost) + "        ";
    }
    cout << endl;
    cout << "Card:";
    for (auto & card : *hand->getHandVector()) {
        cout << setw(17) << card->getName();
    }
    cout << "\n" << endl;
}

int Game::selectStartingRegion() {
    // TODO：确定一个起始的Region，需要查看游戏规则
    return 13;
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



