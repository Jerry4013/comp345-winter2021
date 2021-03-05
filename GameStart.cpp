//
// Created by jingyi on 3/5/2021.
//

#include "GameStart.h"

Game::Game() {
    numOfPlayer = 2;
}

Game::Game(int numOfPlayer) {
    this->numOfPlayer = numOfPlayer;
}

Game::~Game() {

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
		//cout << counter <<". "<<entry.path() << std::endl;
		//counter++;
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
   			if(filepathoption<1 || filepathoption>mapfiles.size())
   				throw string("Unknow option, please chose again!");
   			else if(filepathoption==mapfiles.size()){
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

void Game::startup() {

}

void Game::play() {

}

void Game::computeScore() {

}
