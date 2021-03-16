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
vector<string> Game::COLORS = {"purple", "white", "green", "grey"};

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
    deck->shuffleDeck();
    hand = new Hand(deck); // draw six cards
    //printSixCards();
    createArmiesAndCities();
    bid();
}

void Game::play() {
    cout << "****************************" << endl;
    cout << "     Main Game starts!" << endl;
    cout << "****************************" << endl;
    bool gameEnd = players[0]->getCards().size() == 13;
    int cardIndex;
    while (!gameEnd) {
        for (int i : order) {
            cout << "It's player " << i << "'s turn:\n" << endl;
            Player* currentPlayer = getPlayerById(i);
            // TODO: 给玩家一些行动选择，比如查看地图以及其他各种信息
            printSixCards();
            while (true) {
                cout << "Please select a card (1-6):" << endl;
                cout << ">> ";
                cin >> cardIndex;
                cardIndex--;
                if (currentPlayer->getCoins() < CARD_COSTS[cardIndex]) {
                    cout << "ERROR! You don't have enough coin to buy this card!" << endl;
                    cout << "Try again." << endl;
                } else {
                    break;
                }
            }
            currentPlayer->PayCoin(CARD_COSTS[cardIndex]);
            currentPlayer->exchange((*hand->getHandVector())[cardIndex]);
            // TODO 玩家得到good, 然后action

            // Part 5
            hand->exchange(cardIndex + 1, deck);
            printSixCards();
        }
        // TODO： 暂时把回合数改成2,记得改回13
        gameEnd = players[0]->getCards().size() == 2;
    }
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
        try{
            cout << "Please chose your game map"<< endl;
            for(int i = 0; i < mapFiles.size(); i++) {
                cout << i + 1 << ". " << mapFiles[i] << endl;
            }
            cout << mapFiles.size() + 1 << ". Exit" << endl;
            cout << ">> ";
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
    this->startregionid = selectStartingRegion();
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
    vector<string> colorsCopy = COLORS;
    for (int i = 0; i < numOfPlayer; ++i) {
        cout << "Please enter the full name of player " << i + 1 << ": (separate by space)" << endl;
        cout << ">> ";
        cin >> firstName;
        cin >> lastName;
        while(true){
            cout << "Please enter the color of player " << i + 1 << ": (";
            //purple, white, green, grey) " << endl;
            for(auto item:colorsCopy){
                cout << item <<",";
            }
            cout << ")"<<endl;
            cout << ">> ";
            cin >> color;
            vector<string>::iterator itr = std::find(colorsCopy.begin(), colorsCopy.end(), color);
            if (itr != colorsCopy.end()){
                colorsCopy.erase(itr);
                break;
            }
            else{
                cout << "ERROR! Please type the correct color name"<<endl;
            }
        }
        cout << "Please enter the bidding of player " << i + 1 << ":" << endl;
        cout << ">> ";
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
    Territory *starting_Territory = map->getTerritoryById(startregionid);
    cout << "Start region is" << (*starting_Territory).getName() <<endl;
    for ( auto player : this->players ){
        //(*starting_Territory).placeNewArmiesOfPlayer(player->getId(),4);
        player->PlaceNewArmies(4,(*starting_Territory));
    }
    if ( players.size() ==2 ){
        int territoryid=-1;
        //Assume local army has playerid of 0
        int i = 0;
        while( i < 10 ){
            cout << "Player " << players[i%2]->getId() << ", please select a territory from 1-";
            cout << map->getTerritories().size() << endl;
            cin >> territoryid;
            if ( territoryid<1
                || territoryid>map->getTerritories().size() )
                cout << "Invalid territory ID! Please input another one" << endl;
            else  i++;
            map->getTerritoryById(startregionid)->placeNewArmiesOfPlayer(0,1);
        }
    }

    for(auto player:this->players){
        cout << *player;
    }

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

bool Game::criteriaB(vector<int> neighbors){
    vector<int> neighborsOfNeighbor;
    for ( int neighbor = 0; neighbor < neighbors.size(); ++neighbor ) {
        neighborsOfNeighbor = map->getTerritoryNeighborsById(neighbors[neighbor]);
        for ( int i = 0; i < neighborsOfNeighbor.size(); ++i ) {
            if( map->getDistance(neighbors[neighbor], neighborsOfNeighbor[i]) == 3)  return true;
        }
    }
    return false;
}

int Game::selectStartingRegion() {
    int size = map->getTerritories().size();
    vector<int> TerritoryId(size);
    vector<int> neighbors;
    //Creating a vector of 1-size
    iota(TerritoryId.begin(), TerritoryId.end(),1);
    //Random shuffle territory IDs
    random_shuffle(TerritoryId.begin(), TerritoryId.end());
    int temp_result = 0;
    int counter = 0;
    for (int regionIndex = 0; regionIndex <= size; ++regionIndex){
        neighbors = map->getTerritoryNeighborsById(TerritoryId[regionIndex]);
        for (int neighbor = 0; neighbor < neighbors.size(); ++neighbor){
            //Criteria A and B's second condition
            if ( map->getDistance(TerritoryId[regionIndex],neighbors[neighbor])==3 )  counter++;
        }
        if ( counter >= 2 )  temp_result=TerritoryId[regionIndex];
        else if ( criteriaB(neighbors) )  temp_result=TerritoryId[regionIndex];
        if ( temp_result )  return temp_result;
    }
    return temp_result;
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



