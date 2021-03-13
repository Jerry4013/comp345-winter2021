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

void Game::start() {
    string filepath;
    bool exit;
    namespace fs = std::filesystem;
    cout <<string(20,*)<<endl;
    cout << "Eight-Minute_Empire_Legends."<<endl;
    cout <<string(20,*)<<endl;

    string path = "../Maps/";
    vector<string> mapfiles;
    for (const auto & entry : fs::directory_iterator(path)){
        mapfiles.push_back(entry.path().erase(entry.path().find(path),path.size()));
    }
    MapLoader *ml = new MapLoader();
    int filepathoption=-1;

    //Map selection
    while(true){
        try{
            cout << "Please chose your game map"<<endl;
            for(int i = 0;i<mapfiles.size();i++)
                cout << i+1 <<". "<<mapfiles[i] <<endl;
            cout <<mapfiles.size()<<". Exit"<<endl;

            cout << ">>";
            cin >> filepathoption;
            if(filepathoption<1 || filepathoption>(mapfiles.size()+1))
                throw string("Unknow option, please chose again!");
            else if(filepathoption==mapfiles.size()+1){
                cout <<"GOODBYE"<<endl;
                exit=true;
                break;
            }
            filepath=path+mapfiles[filepathoption-1];
            this->map=ml.loadMap(filepath);
            break;
        }
        catch(const std::string e) {
            cout << e<<endl;
        }
    }

    //Player creation
    string name;
    int biding;
    int coins;
    Territory territory1("territory1", 1, 1);
    Territory territory2("territory2", 2, 2);

    cout << "Enter player firstName: ";
    cin >> name;
    cout << "Enter biding coins: ";
    cin >> biding;
    cout << "Enter initial coins: ";
    cin >> coins;
    vector<Territory*> territories;
    territories.push_back(&territory1);
    territories.push_back(&territory2);
    Player userCreatedPlayer1(name, biding, coins, territories);

    cout << "Enter player firstName: ";
    cin >> name;
    cout << "Enter biding coins: ";
    cin >> biding;
    cout << "Enter initial coins: ";
    cin >> coins;
    vector<Territory*> territories;
    territories.push_back(&territory1);
    territories.push_back(&territory2);
    Player userCreatedPlayer2(name, biding, coins, territories);
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
