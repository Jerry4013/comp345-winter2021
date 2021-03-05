//
// Created by jerry on 2/26/2021.
//

#include "Game.h"

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
   			ml.loadMap(filepath);
   			break;
   		}
   		catch(const std::string e) {
        	cout << e<<endl;
   		}
   	}
}

void Game::startup() {

}

void Game::play() {

}

void Game::computeScore() {

}
