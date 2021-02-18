//
// Created by Luojia yan on 2021-02-07.
//


#include "Map.h"
#include "iostream"
#include <sstream>
using namespace std;


Territory::Territory(){
    this->TerritoryNumber = -1;
    this->ContinentNumber = -1;
    this->TerritoryName = "None";
    for(int i = 0;i<4;i++){
        PlayerArmyArray[i]=0;
    }

};

Territory::~Territory(){};
Territory:: Territory(std::string TerritoryName,int TerritoryNumber,int ContinentNumber){
    this->TerritoryNumber = TerritoryNumber;
    this->TerritoryName = TerritoryName;
    this->ContinentNumber = ContinentNumber;
    this->territoryArmies = {
            { "player1", 0 },
            { "player2", 0 },
            { "player3", 0 },
            { "player4", 0 }};
    this->territoryCities = {
            { "player1", 0 },
            { "player2", 0 },
            { "player3", 0 },
            { "player4", 0 }};
};
//getter
int Territory::GetTerritoryNumber(){return this->TerritoryNumber;}

//TODO::Made change
int Territory::GetContinentNumber() {return this->ContinentNumber;}
string Territory::GetTerritoryName(){return this->TerritoryName;};
//int Territory::GetNumTroops(){cout<<this->GetTerritoryName()<<" has troops: "<<this->NumberOfTroops<<endl;return this->NumberOfTroops;};
//string Territory::GetPlayerName(){return this->OwnerName;};
int Territory::GetNumTroops(string PlayerNumber){
    cout<<PlayerNumber<<" has "<<this->territoryArmies[PlayerNumber]<<" armies at territory "<<this->TerritoryNumber <<endl;
    return this->territoryArmies[PlayerNumber];
}

//setter
void Territory::SetNumTroops(string PlayerNum,int NumOfTroops){
    this->territoryArmies[PlayerNum] = NumOfTroops;
};


int Territory::getCities(const string& playerName) {
    cout<<playerName<<" has "<<this->territoryCities[playerName]<<" cities at territory "<<this->TerritoryNumber <<endl;
    return this->territoryCities[playerName];
}

void Territory::setCities(const string& playerName, int number) {
    this->territoryArmies[playerName] = number;
}


string Territory::toString() const {
    stringstream ss;
    ss << "Territory{ TerritoryName=" << TerritoryName << "; ";
    ss << "TerritoryNumber=" << TerritoryNumber << "; ";
    ss << "ContinentNumber=" << ContinentNumber << "; ";
    ss << "territoryArmies={";
    for (const auto &[k, v] : territoryArmies) {
        ss << "Armies[" << k << "] = " << v << " " << endl;
    }
    for (const auto &[k, v] : territoryCities) {
        ss << "Cities[" << k << "] = " << v << " " << endl;
    }
    return ss.str();
}

ostream &operator<<(ostream &out, const Territory &territory) {
    out << "Territory{ TerritoryName=" << territory.TerritoryName << "; ";
    out << "TerritoryNumber=" << territory.TerritoryNumber << "; ";
    out << "ContinentNumber=" << territory.ContinentNumber << "; ";
    out << "territoryArmies={";
    for (const auto &[k, v] : territory.territoryArmies) {
        out << "Armies[" << k << "] = " << v << "; ";
    }
    out << "};  territoryCities={";
    for (const auto &[k, v] : territory.territoryCities) {
        out << "Cities[" << k << "] = " << v << "; ";
    }
    out << "}";
    return out;
}

//TODO::Made change
void Map::AddEdgesCountry(Territory *t1,Territory *t2){
    int TerritoryOne=t1->GetTerritoryNumber()-1;
    int TerritoryTwo=t2->GetTerritoryNumber()-1;
    if(t1->GetContinentNumber()==t2->GetContinentNumber()){
        territoryMatrix[TerritoryOne][TerritoryTwo]=1;
        //TerritoryMatrix[TerritoryTwo][TerritoryOne]=1;
    }
    else{
        territoryMatrix[TerritoryOne][TerritoryTwo]=3;
        //TerritoryMatrix[TerritoryTwo][TerritoryOne]=3;
        continentMatrix[t1->GetContinentNumber()-1][t2->GetContinentNumber()-1]=t1->GetTerritoryNumber();
        //ContinentMatrix[t2->GetContinentNumber()-1][t1->GetContinentNumber()-1]=t2->GetTerritoryNumber();
    }

};

void Map::DeleteEdgesCountry(int TerritoryOne,int TerritoryTwo){
    territoryMatrix[TerritoryOne][TerritoryTwo]=0;
    territoryMatrix[TerritoryTwo][TerritoryOne]=0;
};

//add delete edges
void Map::AddEdgesContinents(int ContinentOne,int ContinentTwo){
    continentMatrix[ContinentOne][ContinentTwo]=3;
    continentMatrix[ContinentTwo][ContinentOne]=3;

};
void Map::DeleteEdgesContinents(int ContinentOne,int ContinentTwo){
    continentMatrix[ContinentOne][ContinentTwo]=0;
    continentMatrix[ContinentTwo][ContinentOne]=0;
};


void Map::PrintContinentMatrix() {
    cout << "Continent Matrix" <<endl;
    for(int i = 0;i < continentMatrix.size();i++){
        cout << "    "  << i;
    }
    cout<<endl;
    for(int i = 0;i < continentMatrix.size();i++){
        cout << i ;
        for(int j = 0;j < continentMatrix.size();j++){
            cout <<"  "<< continentMatrix[i][j]<<"  ";
        }
        cout <<endl;
    }
}
void Map::PrintTerritoryMatrix() {
    cout << "Territory Matrix" <<endl;
    for(int i = 0;i < territoryMatrix.size();i++){
        cout << "    "  << i;
    }
    cout<<endl;
    for(int i = 0;i < territoryMatrix.size();i++){
        cout << i ;
        for(int j = 0;j < territoryMatrix.size();j++){
            cout <<"  "<< territoryMatrix[i][j]<<"  ";
        }
        cout <<endl;
    }
}





Continent::Continent(std::string name,int ContinentNumber) {
    this->territories = std::vector<Territory*>();
    this->Continetname = name;
    this->ContinentNum = ContinentNumber;
}
Continent::~Continent() {}

//method get continent name
std::string Continent::GetContinentName() {
    return this->Continetname;
}
//method add territory
void Continent::AddTerritory(Territory* Territory){
    this->territories.push_back(Territory);
}
//method return terriroty value
std::vector<Territory*> Continent::ReturnTerritory(){
    return this->territories;
}

//method get continent name
int Continent::GetContinentNum(){
    return this->ContinentNum;
};


//map
Map::Map(std::string mapName, int numberOfContinents, int numberOfRegions){
    this->MapName = mapName;
    //this->continents = std::vector<Continent*>();
    //continentmatrix = std::vector<std:vector<int>>

    for(int i = 0; i < numberOfContinents; i++){
        vector<int> row(numberOfContinents);
        continentMatrix.push_back(row);
    }
    for(int i = 0; i < numberOfRegions; i++){
        vector<int> row(numberOfRegions);
        territoryMatrix.push_back(row);
    }
}
Map::~Map() {}

//TODO::Made change
void Map::AddContinent(Continent* continent) {
    this->continent_hashmap.insert(std::make_pair(continent->GetContinentNum(),continent));
}
std::string Map::GetMapName() {
//    std::cout << "The map name is:  "<<this->MapName<<"\n";
    return this->MapName;
}
std::vector<Continent*> Map::ReturnContient(){
    for(int i=0;i<this->continents.size();i++)
    {
//        cout<< "The map "<<this->MapName<<" has these continents: " <<this->continents[i]->GetContinentName()<<" ";
    }
//    cout<< "\n";
    return this->continents;
}

//TODO::Made change
std::unordered_map<int,Continent*> Map::ReturnContinentHashMap() {
    return this->continent_hashmap;
}

bool Map::CheckTerritoryBelongToOneContinent(Map* map){
    int error = 0;
    //
    for(int i = 1; i <= continentMatrix.size(); i++){
       for(int j = 0; j<map->ReturnContinentHashMap()[i]->ReturnTerritory().size();j++) {
           if (map->ReturnContinentHashMap()[i]->ReturnTerritory()[j]->GetContinentNumber()!=0){
               cout << map->ReturnContinentHashMap()[i]->ReturnTerritory()[j]->GetTerritoryName() << " only belongs to  "
               << map->ReturnContinentHashMap()[i]->GetContinentName()<<endl;
           }
           else{
               error++;
               cout << map->ReturnContinentHashMap()[i]->ReturnTerritory()[j]->GetTerritoryName() << " does not belong to any continent "<<endl;
           }
       }
    }
    if(error ==0){return true;}
    else {return false;}

}


void Map::traverseTerritory(int u, bool visited[]){
    visited[u] = true; //mark v as visited
    for(int v = 0; v<territoryMatrix.size(); v++) {
        if(territoryMatrix[u][v]) {
            if(!visited[v])
                traverseTerritory(v, visited);
        }
    }
};
void Map::traverseContinent(int u, bool visited[]){
    visited[u] = true; //mark v as visited
    for(int v = 0; v < continentMatrix.size(); v++) {
        if(continentMatrix[u][v]) {
            if(!visited[v])
                traverseContinent(v, visited);
        }
    }

};

bool Map::validateTerritory(){
    bool *vis = new bool[territoryMatrix.size()];
    //for all vertex u as start point, check whether all nodes are visible or not
    for(int u=0; u < territoryMatrix.size(); u++) {
        for(int i = 0; i<territoryMatrix.size(); i++)
            vis[i] = false; //initialize as no node is visited
        traverseTerritory(u, vis);
        for(int i = 0; i<territoryMatrix.size(); i++) {
            if(!vis[i]) //if there is a node, not visited by traversal, graph is not connected
                return false;
        }
    }
    return true;

};

bool Map::validateContinent(){
    bool *vis = new bool[continentMatrix.size()];
    //for all vertex u as start point, check whether all nodes are visible or not
    for(int u=0; u < continentMatrix.size(); u++) {
        for(int i = 0; i < continentMatrix.size(); i++)
            vis[i] = false; //initialize as no node is visited
        traverseContinent(u, vis);
        for(int i = 0; i < continentMatrix.size(); i++) {
            if(!vis[i]) //if there is a node, not visited by traversal, graph is not connected
                return false;
        }
    }
    return true;

};



void Map::Validate(Map* map){
    if(CheckTerritoryBelongToOneContinent(map)){
        cout <<endl<< "Each country belongs to one and only one continent"<<endl;
    }
    else
        cout << "Each country does not belong only one continent"<<endl;
    if(validateTerritory()){
        cout << "The map is connected graph"<<endl;
    }
    else
        cout << "The map is not connected graph"<<endl;

    if(validateContinent()){
        cout << "The Continent graph is connected graph"<<endl;
    }
    else
        cout << "The Continent graph is not connected graph"<<endl;

}

vector<vector<int> > &Map::getContinentMatrix() {
    return continentMatrix;
}

vector<vector<int> > &Map::getTerritoryMatrix() {
    return territoryMatrix;
};






