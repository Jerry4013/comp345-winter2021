//
// Created by Luojia yan on 2020-11-21.
//
#include "Map.h"
#include "iostream"
using namespace std;

Territory::Territory(){
    this->TerritoryNumber = 0;
    this->TerritoryName = "None";
    this->NumberOfTroops = 0;
    this->OwnerName = "None";
    this->ContinentNum = 0;
    this->ContinentName = "None";
};
Territory::~Territory(){};


Territory::Territory(int TerritoryNumber,std::string TerritoryName,int NumberOfTroops,std::string OwnerName,int ContinentNum,
          std::string ContinentName){
    this->TerritoryNumber = TerritoryNumber;
    this->TerritoryName = TerritoryName;
    this->NumberOfTroops = NumberOfTroops;
    this->OwnerName = OwnerName;
    this->ContinentNum = ContinentNum;
    this->ContinentName = ContinentName;
};

//getter
int Territory::GetTerritoryNumber(){return this->TerritoryNumber;};
string Territory::GetTerritoryName(){return this->TerritoryName;};
int Territory::GetNumOfTroops(){return this->NumberOfTroops;};
string Territory::GetOwnererName(){return this->OwnerName;};
int Territory::GetContinentNumber(){return this->ContinentNum;};
string Territory::GetContinentName(){return this->ContinentName;};

//setter
void Territory::SetTerritoryNumber(int TerritoryNumber){this->TerritoryNumber = TerritoryNumber;};
void Territory::SetTerritoryName(string TerritoryName){this->TerritoryName = TerritoryName;};
void Territory::SetNumOfTroops(int NumOfTroops){this->NumberOfTroops = NumOfTroops;};
void Territory::SetOwnerName(string OwnerName){this->OwnerName = OwnerName;};
void Territory::SetContinentNumber(int ContinentNumber){this->ContinentNum = ContinentNumber;};
void Territory::SetContinentName(string ContinentName){this->ContinentName = ContinentName;};


//check if two territory is neighbor
bool Territory::IsNeighbor(Territory* territory1,Territory* territory2,int Matrix[100][100]){
    //TOD
    if(Matrix[territory1->TerritoryNumber][territory2->TerritoryNumber]==1){
        return true;
    }
    else
        return false;
};


//validate territory
void Territory::validate(Territory* territory){};



//Continent class

Continent::Continent(){
    this->ContinentNum = 0;
    this->Continetname = "None";
    this->BonusValue = 0;
    this->territories = vector<Territory*>();


};
Continent::~Continent(){};
Continent::Continent(int ContinentNum,std::string Continetname,int BonusValue,std::vector<Territory*> territories){};

//getter
int Continent::GetContinentNum(){return this->ContinentNum;};
std::string Continent::GetContinentName(){return this->Continetname;};
int Continent::GetBonusNum(){return BonusValue;};
std::vector<Territory*> Continent::ReturnTerritory(){ return this->territories;};
//setter
void Continent::SetContinentNum(int Continentnum){this->ContinentNum = Continentnum;};
void Continent::SetContinentName(string Continentname){this->Continetname = Continentname;};
void Continent::SetBonusNum(int BonusNumber){this->BonusValue = BonusNumber;};
void Continent::AddTerritory(Territory* territory){this->territories.push_back(territory);};
void Continent::RemoveTerritory(std::vector<Territory*> territories,int TerritoryNum){territories.erase(territories.begin()+TerritoryNum);};





//Occupied By one player
bool Continent::OccupiedByOnePlayer() {
        //TODO
}

//Validation
void Continent::validateContinent(Continent* continent){
    //TODO
};