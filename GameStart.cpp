//
// Created by lllll on 2021-03-13.
//

#include "GameStart.h"

GameStart::GameStart() {
    numOfPlayer = 2;
}

GameStart::GameStart(int numOfPlayer, Map* gameMap) {
    this->numOfPlayer = numOfPlayer;
    this->map = gameMap;
    coinSupply = 36;
    createPlayers();
}

GameStart::~GameStart() {

}

void GameStart::startup() {

}

void GameStart::play() {

}

void GameStart::computeScore() {

}

void GameStart::start() {
    string filepath;
    bool exit;
    namespace fs = std::filesystem;
    cout << "****************************"<<endl;
    cout << "Eight-Minute_Empire_Legends."<<endl;
    cout << "****************************"<<endl;

    string path = "../Maps/";
    vector<string> mapfiles;
    for (const auto & entry : fs::directory_iterator(path)){
        mapfiles.push_back(entry.path().string().erase(entry.path().string().find(path),path.size()));
    }
    MapLoader *ml = new MapLoader();
    int filepathoption=-1;

    //Map selection
    while(true){
        try{
            cout << "Please chose your game map"<<endl;
            for(int i = 0;i<mapfiles.size();i++)
                cout << i+1 <<". "<<mapfiles[i] <<endl;
            cout <<mapfiles.size()+1<<". Exit"<<endl;

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
            this->map=MapLoader::loadMap(filepath);
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

    cout << "Enter player firstName: ";
    cin >> name;
    cout << "Enter biding coins: ";
    cin >> biding;
    cout << "Enter initial coins: ";
    cin >> coins;
    vector<Territory*> territories;
    //Player userCreatedPlayer1(name, biding, coins, territories);

    cout << "Enter player firstName: ";
    cin >> name;
    cout << "Enter biding coins: ";
    cin >> biding;
    cout << "Enter initial coins: ";
    cin >> coins;
    //Player userCreatedPlayer2(name, biding, coins, territories);
}

void GameStart::createPlayers() {
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
        //players.emplace_back(new Player(i + 1, firstName, lastName, color, bidding, coins));
        cout << "Player " << i + 1 << " is created successfully!" << endl;
        cout << players[i];
    }
}