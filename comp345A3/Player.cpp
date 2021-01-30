//
// Created by Luojia yan on 2020-11-21.
//
#include "Player.h"
#include<algorithm>


//default Constructor
Player::Player(){
    this->PlayerName = "None";
    this->territoryList = vector<Territory*>() ;
    this->reinforcementPool=0;
    this->Playerstrategies = new PlayerStrategies();
}

//parameter Constructor
Player::Player(string playerName,vector<Territory*> territoryList,PlayerStrategies* Playerstrategies){
    this->PlayerName = playerName;
    this->territoryList = territoryList;
    this->reinforcementPool=40;
    this->Playerstrategies = new PlayerStrategies();
    this->Playerstrategies->PlayerStatus = Playerstrategies->PlayerStatus;
};
void Player::setStrategies(string status){
    Playerstrategies->PlayerStatus = status;
    if(status =="human"){cout << this->getPlayerName() << "'s status is human now"<<endl;}
    if(status =="aggressive"){cout << this->getPlayerName() << "'s status is aggressive now"<<endl;}
    if(status =="benevolent"){cout << this->getPlayerName() << "'s status is benevolent now"<<endl;}
    if(status =="neutral"){cout << this->getPlayerName() << "'s status is neutral now"<<endl;}
};

//getters:
string Player::getPlayerName(){return this->PlayerName;};
vector<Territory*>Player::getTerritoryList(){return this->territoryList;};
int Player::getReinforcementPool() {return reinforcementPool;}
int Player::getOwnedTerritories() {return ownedTerritoriesCount;}
vector<Order*> Player::getOrdersList() {return player_ordersList;}
Hand Player::getHand() {return playerHand;}

//setters:
void Player::setPlayerName(const string &playerName) { PlayerName = playerName;}
void Player::setTerritoryList(const vector<Territory *> &territoryList) {Player::territoryList = territoryList;}
void Player::setReinforcementPool(int reinforcementPool) {Player::reinforcementPool = reinforcementPool;}


//reinforcementPool related:

void Player::addArmiesToReinforcementPool(int numOfArmies) {
    reinforcementPool += numOfArmies;
}
int Player::TakeArmiesFromReinforcementPool(int numOfArmies) {
    if (numOfArmies > reinforcementPool) {
        numOfArmies = reinforcementPool;
        this->setReinforcementPool(0);
        return numOfArmies;
    }
    else {
        this->setReinforcementPool(reinforcementPool-numOfArmies);
        return numOfArmies;
    }
}


//territory related:

void Player::addTerritory(Territory *territory) {
    string ownerName = territory->GetOwnererName();

    /*
     * this part should be done in gameEngine, since now territory does has Play class anymore,
     * territory now only has a ownerName.
     */

//    //if the territory has a owner, remove the owner from this territory
//    if(player != nullptr){
//        player->removeTerritory(territory);
//    }

    territoryList.push_back(territory);
    territory->SetOwnerName(this->PlayerName);
    ownedTerritoriesCount += 1;
}
void Player::removeTerritory(Territory *territory) {
    vector<Territory*>::iterator removeT;
    removeT = remove(territoryList.begin(),territoryList.end(),territory);
    ownedTerritoriesCount -= 1;
}

//vector<Territory*> Player::toAttack(vector<Territory*> Map) {
//    vector<Territory*> neighborTerritories;
//    bool isAlreadyAdded;
//    //for each territory of the player
//    for (int i = 0; i < territoryList.size(); i++) {
//        //to check with each territory of the map
//        for (int j = 0; j < 100; j++) {
//            //if they are neighbors and if Map[j] isn't owned by the player
//            if (territoryList[i]->IsNeighbor(Map[j]) && territoryList[i]->GetOwnererName() != Map[j]->GetOwnererName()) {
//                //check if this neighbor is already added to the list
//                for (int k = 0; k < neighborTerritories.size(); k++) {
//                    if (neighborTerritories[k]->GetOwnererName() == Map[j]->GetOwnererName()) {
//                        isAlreadyAdded = true;
//                    }
//                }
//                //if it is not added, then add it to the list
//                if (!isAlreadyAdded || neighborTerritories.empty()) {
//                    neighborTerritories.push_back(Map[j]);
//                }
//            }
//        }
//    }
//    return neighborTerritories;
//}
vector<Territory*> Player::toDefend() {
//    defendList = territoryList;
    return this->getTerritoryList();
}


//OrdersList related:

void Player::issueOrder() {


}

/*
 * Now toAttack and toDefend can return a list of the territories that can be attacked or defended.
 * No need to ask user to input the attack or defend list. Most of the user interaction should be done in Orders Issuing phase.
 */

//void Player::issueOrder(vector<Territory> TerritoryList,int ConnectionBufferFromMap[100][100]) {
//
//    int territoryIndex;
//    int finishDefend = 0;
//    int finishAttack = 0;
//    int time = 0;
//    cout << "Please decide which territories are to be defended" << endl;
//    while (finishDefend == 0) {
//        cout<<"enter # of territory in TerritoryList"<<endl;
//        cin>>territoryIndex;
//        if(TerritoryList[territoryIndex].GetPlayerName()==this->getPlayerName()){
//            cout<<"this is your torritory, add to Defendlist"<<endl;
//            this->toDefend(&TerritoryList[territoryIndex]);
//        }
//        else{
//            cout<<"this torritory is not yours"<<endl;
//
//        }
//        cout<<"do you want to end to enter defended torritories? if yes(1)/if no(0)"<<endl;
//        cin>>finishDefend;
//    }
//    cout << "Please decide which territories are to be attacked" << endl;
//    while(finishAttack==0){
//        cout<<"enter # of territory in TerritoryList"<<endl;
//        cin>>territoryIndex;
//        if(TerritoryList[territoryIndex].GetPlayerName()!=this->getPlayerName()){
//            for(int i=0; i<this->playerTerritory.size();i++) {
//                if (ConnectionBufferFromMap[this->playerTerritory[i]->GetTerritoryNumber()][TerritoryList[territoryIndex].GetTerritoryNumber()] ==
//                    1 ||
//                    ConnectionBufferFromMap[TerritoryList[territoryIndex].GetTerri    toryNumber()][this->playerTerritory[i]->GetTerritoryNumber()] ==
//                    1) {
//                    cout << "this torritory is a neighbor of yours torritory, add to Attacklist"<<endl;
//                    this->toAttack(&TerritoryList[territoryIndex]);
//                    time++;
//                }
//            }
//            if(time==0){
//                cout<<"this torritory is not a neighbor of yours torritory"<<endl;
//            }
//
//        }
//        else{
//            cout<<"this torritory is yours torritory"<<endl;
//        }
//        cout<<"do you want to end to enter attacked torritories? if yes(1)/if no(0)"<<endl;
//        cin>>finishAttack;
//    }
//}
