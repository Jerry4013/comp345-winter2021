#include "Player.h"
#include "OrderList.h"
#include<algorithm>
#include <math.h>
#include <iostream>
using namespace std;



Player::Player(string playerName, Hand hand) {
    this->playerName = playerName;
    this->playerHand = hand;
}

Player::Player(string playerName){
    this->playerName = playerName;
}

Player::Player(){


}

//return player name
std::string Player::getPlayerName() {
    return this->playerName;
}

void Player::setPlayerName(string playerName) {
    this->playerName=playerName;

}

//push offend list
void Player::toAttack(Territory *territory) {
    AttackList.push_back(territory);
}


//push defend list
void Player::toDefend(Territory *territory) {
    DefendList.push_back(territory);
}


int Player::getReinforcementPool() {
    return reinforcementPool;
}

void Player::addArmiesToReinforcementPool(int numOfArmies) {
    reinforcementPool += numOfArmies;
}

void Player::setReinforcementPool(int numOfArmies) {
    reinforcementPool = numOfArmies;
}

void Player::addTerritory(Territory *territory) {

    Player* player = territory->GetPlayer();
    if(player != nullptr){
        player->removeTerritory(territory);
    }

    playerTerritory.push_back(territory);
    territory->setPlayer(this);
    ownedTerritoriesCount += 1;
}

void Player::removeTerritory(Territory *territory) {
    vector<Territory*>::iterator removeT;
    removeT = remove(playerTerritory.begin(),playerTerritory.end(),territory);
    ownedTerritoriesCount -= 1;
}

int Player::TakeArmiesFromReinforcementPool(int numOfArmies) {
    if (numOfArmies > reinforcementPool){
        numOfArmies = reinforcementPool;
        this->setReinforcementPool(0);
        return numOfArmies;
    }
    else{
        this->setReinforcementPool(reinforcementPool-numOfArmies);
        return numOfArmies;
    }
}

int Player::getOwnedTerritories() {
    return ownedTerritoriesCount;
}

vector<Order*> Player::getOrdersList() {
    return player_ordersList->getOrdersList();
}

Hand& Player::getHand() {
    return playerHand;
}

//use switch to issue order in differenet situations.
void Player::issueOrder(vector<Territory> TerritoryList,int ConnectionBufferFromMap[100][100]) {

    int territoryIndex;
    int finishDefend = 0;
    int finishAttack = 0;
    int time = 0;
    cout << "Please decide which territories are to be defended" << endl;
    while (finishDefend == 0) {
        cout<<"enter # of territory in TerritoryList"<<endl;
        cin>>territoryIndex;
        if(TerritoryList[territoryIndex].GetPlayerName()==this->getPlayerName()){
            cout<<"this is your torritory, add to Defendlist"<<endl;
            this->toDefend(&TerritoryList[territoryIndex]);
        }
        else{
            cout<<"this torritory is not yours"<<endl;

        }
        cout<<"do you want to end to enter defended torritories? if yes(1)/if no(0)"<<endl;
        cin>>finishDefend;
    }
    cout << "Please decide which territories are to be attacked" << endl;
    while(finishAttack==0){
        cout<<"enter # of territory in TerritoryList"<<endl;
        cin>>territoryIndex;
        if(TerritoryList[territoryIndex].GetPlayerName()!=this->getPlayerName()){
            for(int i=0; i<this->playerTerritory.size();i++) {
                if (ConnectionBufferFromMap[this->playerTerritory[i]->GetTerritoryNumber()][TerritoryList[territoryIndex].GetTerritoryNumber()] ==
                    1 ||
                    ConnectionBufferFromMap[TerritoryList[territoryIndex].GetTerritoryNumber()][this->playerTerritory[i]->GetTerritoryNumber()] ==
                    1) {
                    cout << "this torritory is a neighbor of yours torritory, add to Attacklist"<<endl;
                    this->toAttack(&TerritoryList[territoryIndex]);
                    time++;
                }
            }
            if(time==0){
                cout<<"this torritory is not a neighbor of yours torritory"<<endl;
            }

        }
        else{
            cout<<"this torritory is yours torritory"<<endl;
        }
        cout<<"do you want to end to enter attacked torritories? if yes(1)/if no(0)"<<endl;
        cin>>finishAttack;
    }
}





//    switch (orderType) {
//
//        case 1: {
//            Order* order = new Deploy();
////            player_ordersList.queue(order);
//            cout << "New deploy order has been issued to the order list." << endl;
//            break;
//        }
//        case 2: {
//            Order* order = new Advance();
////            player_ordersList.queue(order);
//            cout << "New advance order has been issued to the order list." << endl;
//        }
//        case 3: {
//            Order* order = new Bomb();
////            player_ordersList.queue(order);
//            cout << "New bomb order has been issued to the order list." << endl;
//            break;
//        }
//        case 4: {
//            Order* order = new Blockade();
////            player_ordersList.queue(order);
//            cout << "New blockade order has been issued to the order list." << endl;
//            break;
//        }
//        case 5: {
//            Order* order = new Airlift();
////            player_ordersList.queue(order);
//            cout << "New airlift order has been issued to the order list." << endl;
//            break;
//        }
//        case 6: {
//            Order* order = new Negotiate();
////            player_ordersList.queue(order);
//            cout << "New negotiate order has been issued to the order list." << endl;
//            break;
//        }
//        case 7: {
//            Order* order = new Reinforcement();
////            player_ordersList.queue(order);
//            cout << "New reinforcement order has been issued to the order list." << endl;
//            break;
//        }

//    }




