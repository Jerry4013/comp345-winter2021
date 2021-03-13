//
// Created by jerry on 2/26/2021.
//

#include <sstream>
#include "Game.h"

Game::Game() {
    numOfPlayer = 2;
}

Game::Game(int numOfPlayer, Map* gameMap) {
    this->numOfPlayer = numOfPlayer;
    this->map = gameMap;
    coinSupply = 36;
    createPlayers();
}

Game::~Game() {

}

void Game::startup() {

}

void Game::play() {

}

void Game::computeScore() {

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
        cout << "Please enter the name of player " << i + 1 << ":" << endl;
        getline(cin, name);
        stringstream ss(name);
        ss >> firstName;
        ss >> lastName;
        cout << "Please enter the color of player " << i + 1 << ":" << endl;
        cin >> color;
        cout << "Please enter the bidding of player " << i + 1 << ":" << endl;
        cin >> bidding;
        coinSupply -= coins;
        players.emplace_back(new Player(i + 1, firstName, lastName, color, bidding, coins));
        cout << "Player " << i + 1 << " is created successfully!" << endl;
        cout << players[i];
    }
}
