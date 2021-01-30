#include "OrdersLists.h"
#include "GameEngine.h"
#include <algorithm>

//Orders
Order::Order() : player() {}

Order::Order(Player* player) {
    this->player = player;
}

Order::Order(const Order& toCopy) {
    player = new Player(*toCopy.player);
    wasExecuted = toCopy.wasExecuted;
}

Order::~Order(){}

Order& Order::operator=(const Order& rightSide) {
    player = new Player(*(rightSide.player));
    wasExecuted = rightSide.wasExecuted;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Order& toOutput) {
    return toOutput.doPrint(out);
}


//Deploy
Deploy::Deploy() : Order(), territoryToDeploy(), numOfArmies(){}

Deploy::Deploy(Player* player, Territory* target, int numOfArmies) :
Order(player),territoryToDeploy(target), numOfArmies(numOfArmies)
{}

Deploy::Deploy(const Deploy& toCopy) : Order(toCopy) {
    this->territoryToDeploy = new Territory(*toCopy.territoryToDeploy);
    this->numOfArmies = toCopy.numOfArmies;
}

Deploy& Deploy::operator=(const Deploy& rightSide) {
    Order::operator=(rightSide);
    territoryToDeploy = new Territory(*rightSide.territoryToDeploy);
    numOfArmies = rightSide.numOfArmies;
    return *this;
}

Deploy::~Deploy() {}

bool Deploy::validate() {
    bool playerOwnsTerritory = (territoryToDeploy->GetOwnererName() == player->getPlayerName());
    bool numOfArmiesValid = (numOfArmies > 0 && numOfArmies<=player->getReinforcementPool());
    if(playerOwnsTerritory && numOfArmiesValid){
        return true;
    }
    else{
        cout<<"it is not valid!"<<endl;
        return false;
    }

}

void Deploy::execute() {
    int newNumberOfArmies =territoryToDeploy->NumberOfTroops + numOfArmies;
    territoryToDeploy->SetNumOfTroops(newNumberOfArmies);
    wasExecuted = true;
    std::cout << "Deploying "<<numOfArmies <<" armies into territory: "<<territoryToDeploy->GetTerritoryName()
    <<" Now it has "<<territoryToDeploy->GetNumOfTroops()<<" armies"<<endl;
    cout<<"Deploy end"<<endl;
}
string Deploy::getType() {
    return "Deploy";
}
std::ostream& Deploy::doPrint(std::ostream& out) const {
    out << "Deploy order.";
    if (wasExecuted) {
        out << " This order was executed, its effect was {effect}.";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Deploy& toOutput) {
    return toOutput.doPrint(out);
}


//Advance
Advance::Advance() : Order(), fromTerritory(), toTerritory(), numOfArmies() {}

Advance::Advance(Player* player, Territory* fromTerritory, Territory* toTerritory,int numOfArmies ) : Order(player) {
    this->fromTerritory = fromTerritory;
    this->toTerritory = toTerritory;
    this->numOfArmies = numOfArmies;
}
Advance::Advance(const Advance& toCopy) : Order(toCopy) {
    this->fromTerritory = new Territory(*toCopy.fromTerritory);
    this->toTerritory = new Territory(*toCopy.toTerritory);
    this->numOfArmies = toCopy.numOfArmies;
}

Advance::~Advance() {}

Advance& Advance::operator=(const Advance& rightSide) {
    Order::operator=(rightSide);
    fromTerritory = new Territory(*rightSide.fromTerritory);
    toTerritory = new Territory(*rightSide.toTerritory);
    numOfArmies = rightSide.numOfArmies;
    return *this;
}

bool Advance::validate() {
    if(player->getPlayerName()!=fromTerritory->GetOwnererName()){
        cout<<"this is not your own territory, it is not valid!"<<endl;
        return false;
    }
    if(numOfArmies<=0){
        cout<<"numOfArmies is 0 or less, it is not valid!"<<endl;
        return false;
    }
    return true;
}

void Advance::execute() {
    if (!validate()) {
        cout<<"Not valided!!"<<endl;
        return ;
    }
    if(numOfArmies>fromTerritory->GetNumOfTroops()){
        numOfArmies=fromTerritory->GetNumOfTroops();
    }
    wasExecuted = true;
    if(fromTerritory->GetOwnererName()==toTerritory->GetOwnererName()){
        fromTerritory->SetNumOfTroops(fromTerritory->GetNumOfTroops()-numOfArmies);
        toTerritory->SetNumOfTroops(toTerritory->GetNumOfTroops()+numOfArmies);
        cout<<"from "<<fromTerritory->GetTerritoryName()<<" move to "<<toTerritory->GetTerritoryName()
            <<", Now it has "<<toTerritory->GetNumOfTroops()<<" armies"<<endl;
        cout<<"Advance end"<<endl;
    }
    else {
        int numOfDefend = toTerritory->GetNumOfTroops();
        int numOfOffend = numOfArmies;
        while(numOfDefend!=0&&numOfOffend!=0){
            int random1= rand()%10+1;
            int random2= rand()%10+1;
            if(random1<7){
                numOfDefend--;
            }
            if(random2<8){
                numOfOffend--;
            }
        }
        if(numOfOffend==0){
            fromTerritory->SetNumOfTroops(fromTerritory->GetNumOfTroops()-numOfArmies);
            toTerritory->SetNumOfTroops(numOfDefend);
            cout<<"all invading armies have been killed."<<"Now it has "<<toTerritory->GetNumOfTroops()<<" armies"<<endl;

        }
        if(numOfDefend==0){
            fromTerritory->SetNumOfTroops(fromTerritory->GetNumOfTroops()-numOfArmies);
            toTerritory->SetNumOfTroops(numOfOffend);
            cout<<"all defending armies have been killed"<<fromTerritory->GetOwnererName()<<" conquer "<<toTerritory->GetOwnererName()<<endl;
            cout<<"Now this territory has "<<toTerritory->GetNumOfTroops()<<" armies"<<endl;


            string playName=toTerritory->GetOwnererName();
            int territoryNum=toTerritory->TerritoryNumber;
            toTerritory->SetOwnerName(fromTerritory->GetOwnererName());
            //由于toTerritory 无player data member无法删除防守方的TerritoryList;
            //只可添加到进攻方的TerritoryList
            player->territoryList.push_back(toTerritory);
            for (int k = 0; k < player->territoryList.size(); k++) {
                cout <<player->getPlayerName()<< " has : "<< player->territoryList[k]->TerritoryNumber<<endl;

            }

            for(int i=0;i<PlayerList.size();i++){
                if(playName==PlayerList[i]->getPlayerName()){
                    for(int j=0;j<PlayerList[i]->territoryList.size();j++){
                        if(PlayerList[i]->territoryList[j]->TerritoryNumber==territoryNum){
                            delete PlayerList[i]->territoryList[j];
                            PlayerList[i]->territoryList.erase(PlayerList[i]->territoryList.begin()+j);
                            for (int k = 0; k < PlayerList[i]->territoryList.size(); k++) {
                                cout <<playName<<" "<<PlayerList[i]->getPlayerName()<< " has : "<< PlayerList[i]->territoryList[k]->TerritoryNumber<<endl;

                            }
                        }
                    }

                }
            }


        }

    }
    wasExecuted = true;
    std::cout << "Advance end.\n";
}

string Advance::getType() {
    return "Advance";
}

std::ostream& Advance::doPrint(std::ostream& out) const {
    out << "Advance order.";
    if (wasExecuted) {
        out << " This order was executed, its effect was {effect}.";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Advance& toOutput) {
    return toOutput.doPrint(out);
}


//Bomb
Bomb::Bomb() : Order(), toTerritory() {}

Bomb::Bomb(Player* player, Territory* toTerritory) : Order(player) {
    this->toTerritory = toTerritory;
}

Bomb::Bomb(const Bomb& toCopy) : Order(toCopy) {
    this->toTerritory =new Territory(*toCopy.toTerritory);
}

Bomb::~Bomb() {}

Bomb& Bomb::operator=(const Bomb& rightSide) {
    Order::operator=(rightSide);
    toTerritory = new Territory(*rightSide.toTerritory);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Bomb& toOutput) {
    return toOutput.doPrint(out);
}

bool Bomb::validate() {
    if(player->getPlayerName()==toTerritory->GetOwnererName()){
        cout<<"this is your own territory, it is not valid!"<<endl;
        return false;
    }
    return true;
}

void Bomb::execute() {
    if (!validate()) {
        cout<<"Not valided!!"<<endl;
        return ;
    }
    int half = toTerritory->GetNumOfTroops()/2;
    toTerritory->SetNumOfTroops(half);

    wasExecuted = true;
    std::cout <<toTerritory->GetTerritoryName() <<"has been bombed."<<half<<" armies remain"<<endl;
    cout<<"Bomb end"<<endl;
}
string Bomb::getType() {
    return "Bomb";
}
std::ostream& Bomb::doPrint(std::ostream& out) const {
    out << "Bomb order.";
    if (wasExecuted) {
        out << " This order was executed, its effect was {effect}.";
    }
    return out;
}
//-----------------------------------------------------------------------------//

//Blockade
Blockade::Blockade() : Order(), TerritoryBlocked() {}

Blockade::Blockade(Player* player, Territory* TerritoryBlocked) : Order(player) {
    this->TerritoryBlocked = TerritoryBlocked;

    //do actions
}

Blockade::Blockade(const Blockade& toCopy) : Order(toCopy) {
    this->TerritoryBlocked = toCopy.TerritoryBlocked;
}

Blockade::~Blockade() {}

Blockade& Blockade::operator=(const Blockade& rightSide) {
    Order::operator=(rightSide);
    TerritoryBlocked = rightSide.TerritoryBlocked;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Blockade& toOutput) {
    return toOutput.doPrint(out);
}

bool Blockade::validate() {
    bool playerOwnsTerritory = (TerritoryBlocked->GetOwnererName() == player->getPlayerName());
    return playerOwnsTerritory;
}

void Blockade::execute() {
    if (!validate()) {
        cout<<"Not valided!!"<<endl;
        return ;
    }
    wasExecuted = true;
    TerritoryBlocked->SetNumOfTroops(TerritoryBlocked->GetNumOfTroops()*2);
    TerritoryBlocked->SetOwnerName("Netural");
    cout<<"this territory has "<<TerritoryBlocked->GetNumOfTroops()<<" armies and owner name is "<<TerritoryBlocked->GetOwnererName()<<endl;
    cout<<"Blockade end."<<endl;
}

string Blockade::getType(){
    return "Blockade";
}

std::ostream& Blockade::doPrint(std::ostream& out) const {
    out << "Blockade order.";
    if (wasExecuted) {
        out << " This order was executed, its effect was {effect}.";
    }
    return out;
}


//Airlift
Airlift::Airlift() : Order(), fromTerritory(), toTerritory(), numOfArmies() {}

Airlift::Airlift(Player* player, Territory* fromTerritory, Territory* toTerritory,int numOfArmies) : Order(player) {
    this->fromTerritory = fromTerritory;
    this->toTerritory = toTerritory;
    this->numOfArmies = numOfArmies;

    //do actions
}

Airlift::Airlift(const Airlift& toCopy) : Order(toCopy) {
    this->fromTerritory = toCopy.fromTerritory;
    this->toTerritory = toCopy.toTerritory;
//    this->numOfArmies = toCopy.numOfArmies;
}

Airlift::~Airlift() {}

Airlift& Airlift::operator=(const Airlift& rightSide) {
    Order::operator=(rightSide);
    fromTerritory = rightSide.fromTerritory;
    toTerritory = rightSide.toTerritory;
    numOfArmies = rightSide.numOfArmies;
    return *this;
}

bool Airlift::validate() {
     if(player->getPlayerName()!=fromTerritory->GetOwnererName()){
        cout<<"no territory is not your own territory, it is not valid!"<<endl;
        return false;
    }
    if(numOfArmies<=0){
        cout<<"numOfArmies is 0 or less, it is not valid!"<<endl;
        return false;
    }
    return true;;
}

void Airlift::execute() {
    if (!validate()) {
        cout<<"Not valided!!"<<endl;
        return ;
    }
    if(numOfArmies>fromTerritory->GetNumOfTroops()){
        numOfArmies=fromTerritory->GetNumOfTroops();
    }
    wasExecuted = true;
    if(fromTerritory->GetOwnererName()==toTerritory->GetOwnererName()){
        fromTerritory->SetNumOfTroops(fromTerritory->GetNumOfTroops()-numOfArmies);
        toTerritory->SetNumOfTroops(toTerritory->GetNumOfTroops()+numOfArmies);
        cout<<"from "<<fromTerritory->GetTerritoryName()<<" move to "<<toTerritory->GetTerritoryName()
            <<", Now it has "<<toTerritory->GetNumOfTroops()<<" armies"<<endl;
        cout<<"Airlift end"<<endl;
    }
    else {
        int numOfDefend = toTerritory->GetNumOfTroops();
        int numOfOffend = numOfArmies;
        while(numOfDefend!=0&&numOfOffend!=0){
            int random1= rand()%10+1;
            int random2= rand()%10+1;
            if(random1<7){
                numOfDefend--;
            }
            if(random2<8){
                numOfOffend--;
            }
        }
        if(numOfOffend==0){
            fromTerritory->SetNumOfTroops(fromTerritory->GetNumOfTroops()-numOfArmies);
            toTerritory->SetNumOfTroops(numOfDefend);
            cout<<"all invading armies have been killed."<<"Now it has "<<toTerritory->GetNumOfTroops()<<" armies"<<endl;

        }
        if(numOfDefend==0){
            fromTerritory->SetNumOfTroops(fromTerritory->GetNumOfTroops()-numOfArmies);
            toTerritory->SetNumOfTroops(numOfOffend);
            cout<<"all defending armies have been killed"<<fromTerritory->GetOwnererName()<<" conquer "<<toTerritory->GetOwnererName()<<endl;
            cout<<"Now this territory has "<<toTerritory->GetNumOfTroops()<<" armies"<<endl;


            string playName=toTerritory->GetOwnererName();
            int territoryNum=toTerritory->TerritoryNumber;
            toTerritory->SetOwnerName(fromTerritory->GetOwnererName());
            //由于toTerritory 无player data member无法删除防守方的TerritoryList;
            //只可添加到进攻方的TerritoryList
            player->territoryList.push_back(toTerritory);
            for (int k = 0; k < player->territoryList.size(); k++) {
                cout <<player->getPlayerName()<< " has : "<< player->territoryList[k]->TerritoryNumber<<endl;

            }

            for(int i=0;i<PlayerList.size();i++){
                if(playName==PlayerList[i]->getPlayerName()){
                    for(int j=0;j<PlayerList[i]->territoryList.size();j++){
                        if(PlayerList[i]->territoryList[j]->TerritoryNumber==territoryNum){
                            delete PlayerList[i]->territoryList[j];
                            PlayerList[i]->territoryList.erase(PlayerList[i]->territoryList.begin()+j);
                            for (int k = 0; k < PlayerList[i]->territoryList.size(); k++) {
                                cout <<playName<<" "<<PlayerList[i]->getPlayerName()<< " has : "<< PlayerList[i]->territoryList[k]->TerritoryNumber<<endl;

                            }
                        }
                    }

                }
            }


        }

    }
    wasExecuted = true;
    cout<<"Airlift end"<<endl;


}

string Airlift::getType(){
    return "Airlift";
}
    
std::ostream& Airlift::doPrint(std::ostream& out) const {
    out << "Airlift order.";
    if (wasExecuted) {
        out << " This order was executed, its effect was {effect}.";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Airlift& toOutput) {
    return toOutput.doPrint(out);
}


//negotiate
Negotiate::Negotiate() : Order(), player2() {}

Negotiate::Negotiate(Player* player1, Player* player2) : Order(player1) {
    this->player2 = player2;

    //do actions
}

Negotiate::Negotiate(const Negotiate& toCopy) : Order(toCopy) {
    this->player2 = toCopy.player2;
}

Negotiate::~Negotiate() {}

Negotiate& Negotiate::operator=(const Negotiate& rightSide) {
    Order::operator=(rightSide);
    player2 = rightSide.player2;
    return *this;
}

bool Negotiate::validate() {
    bool samePlayer = (player->getPlayerName() == player2->getPlayerName());
    return !samePlayer;
}

void Negotiate::execute() {
    if (!validate()) {
        cout<<"Not valid!!"<<endl;
        return ;
    }
    wasExecuted = true;
    std::cout << "Love and peace!\n";
}
std::string Negotiate::getType(){
    return "Negotiate";
}
std::ostream& Negotiate::doPrint(std::ostream& out) const {
    out << "Negotiate order.";
    if (wasExecuted) {
        out << " This order was executed, its effect was {effect}.";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Negotiate& toOutput) {
    return toOutput.doPrint(out);
}


