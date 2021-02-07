//
// Created by Luojia yan on 2021-02-07.
//


#include "Map.h"
#include "iostream"
using namespace std;

#define NODE 10
int TerritoryMatrix[10][10];
int ContinentMatrix[10][10];



Territory::Territory(){
    this->TerritoryNumber = 0;
    this->TerritoryName = "None";
    this->ContinentName = "None";
    for(int i = 0;i<4;i++){
        PlayerArmyArray[i]=0;
    }

};
Territory::~Territory(){};
Territory:: Territory(std::string TerritoryName,int TerritoryNumber,std::string Continent){
    this->TerritoryNumber = TerritoryNumber;
    this->TerritoryName = TerritoryName;
    this->ContinentName = Continent;
};
//getter
int Territory::GetTerritoryNumber(){return this->TerritoryNumber;};
string Territory::GetTerritoryName(){return this->TerritoryName;};
//int Territory::GetNumTroops(){cout<<this->GetTerritoryName()<<" has troops: "<<this->NumberOfTroops<<endl;return this->NumberOfTroops;};
//string Territory::GetPlayerName(){return this->OwnerName;};
int Territory::GetNumTroops(int PlayerNumber){ return this->PlayerArmyArray[PlayerNumber-1];}


string Territory::GetContinentName(){return this->ContinentName;};
//setter
void Territory::SetNumTroops(int PlayerNum,int NumOfTroops){this->PlayerArmyArray[PlayerNum-1] = NumOfTroops;};


//add delete edges
void HelperFunctionMap::AddEdgesCountry(int TerritoryOne,int TerritoryTwo){
    TerritoryMatrix[TerritoryOne][TerritoryTwo]=1;
    TerritoryMatrix[TerritoryTwo][TerritoryOne]=1;
};
void HelperFunctionMap::DeleteEdgesCountry(int TerritoryOne,int TerritoryTwo){
    TerritoryMatrix[TerritoryOne][TerritoryTwo]=0;
    TerritoryMatrix[TerritoryTwo][TerritoryOne]=0;
};

//add delete edges
void HelperFunctionMap::AddEdgesContinents(int ContinentOne,int ContinentTwo){
    ContinentMatrix[ContinentOne][ContinentTwo]=1;
    ContinentMatrix[ContinentTwo][ContinentOne]=1;

};
void HelperFunctionMap::DeleteEdgesContinents(int ContinentOne,int ContinentTwo){
    ContinentMatrix[ContinentOne][ContinentTwo]=0;
    ContinentMatrix[ContinentTwo][ContinentOne]=0;
};


void HelperFunctionMap::PrintContinentMatrix() {
    cout << "Continent Matrix" <<endl;
    for(int i = 0;i < NODE;i++){
        cout << "    "  << i;
    }
    cout<<endl;
    for(int i = 0;i < NODE;i++){
        cout << i ;
        for(int j = 0;j < NODE;j++){
            cout <<"  "<< ContinentMatrix[i][j]<<"  ";
        }
        cout <<endl;
    }
}
void HelperFunctionMap::PrintTerritoryMatrix() {
    cout << "Territory Matrix" <<endl;
    for(int i = 0;i < NODE;i++){
        cout << "    "  << i;
    }
    cout<<endl;
    for(int i = 0;i < NODE;i++){
        cout << i ;
        for(int j = 0;j < NODE;j++){
            cout <<"  "<< TerritoryMatrix[i][j]<<"  ";
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
    for(int i=0;i<this->territories.size();i++)
    {
//        cout<< this->territories[i]->GetTerritoryName()<<" ";
    }
//    cout<< "\n";
    return this->territories;
}

//method get continent name
int Continent::GetContinentNum(){
    return this->ContinentNum;
};
void Continent::AddEdgeContinent(int FirstContinent,int SecondContinent){
    ContinentMatrix[FirstContinent][SecondContinent] = 1;
};
void Continent::RemoveEdgeContinent(int FirstContinent,int SecondContinent){
    ContinentMatrix[FirstContinent][SecondContinent] = 0;
};


//map
Map::Map(std::string mapname){
    this->MapName = mapname;
    this->continents = std::vector<Continent*>();
}
Map::~Map() {}
void Map::AddContinent(Continent* continent) {
    this->continents.push_back(continent);
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


void Map::CreateContinentMatrix(){
    for(int i = 0;i<NODE;i++){
        for(int j = 0;j<NODE;j++){
            ContinentMatrix[i][j]=0;
        }
    }
};
void Map::CreateCountryMatrix(){
    for(int i = 0;i<NODE;i++){
        for(int j = 0;j<NODE;j++){
            TerritoryMatrix[i][j]=0;
        }
    }
};



bool Map::CheckTerritoryBelongToOneContinent(Map* map){
    int error = 0;
    for(int i = 0; i<map->ReturnContient().size();i++){
       for(int j = 0; j<map->ReturnContient()[i]->ReturnTerritory().size();j++) {
           if (!map->ReturnContient()[i]->ReturnTerritory()[j]->GetContinentName().empty()){
               cout << map->ReturnContient()[i]->ReturnTerritory()[j]->GetTerritoryName() << " only belongs to  "
               << map->ReturnContient()[i]->GetContinentName()<<endl;
           }
           else{
               error++;
               cout << map->ReturnContient()[i]->ReturnTerritory()[j]->GetTerritoryName() << " does not belong to any continent "<<endl;
           }
       }
    }
    if(error ==0){return true;}
    else {return false;}

}


void Map::traverseTerritory(int u, bool visited[]){
    visited[u] = true; //mark v as visited
    for(int v = 0; v<NODE; v++) {
        if(TerritoryMatrix[u][v]) {
            if(!visited[v])
                traverseTerritory(v, visited);
        }
    }
};
void Map::traverseContinent(int u, bool visited[]){
    visited[u] = true; //mark v as visited
    for(int v = 0; v<NODE; v++) {
        if(ContinentMatrix[u][v]) {
            if(!visited[v])
                traverseContinent(v, visited);
        }
    }

};

bool Map::validateTerritory(){
    bool *vis = new bool[NODE];
    //for all vertex u as start point, check whether all nodes are visible or not
    for(int u; u < NODE; u++) {
        for(int i = 0; i<NODE; i++)
            vis[i] = false; //initialize as no node is visited
        traverseTerritory(u, vis);
        for(int i = 0; i<NODE; i++) {
            if(!vis[i]) //if there is a node, not visited by traversal, graph is not connected
                return false;
        }
    }
    return true;

};
bool Map::validateContinent(){
    bool *vis = new bool[NODE];
    //for all vertex u as start point, check whether all nodes are visible or not
    for(int u; u < NODE; u++) {
        for(int i = 0; i<NODE; i++)
            vis[i] = false; //initialize as no node is visited
        traverseContinent(u, vis);
        for(int i = 0; i<NODE; i++) {
            if(!vis[i]) //if there is a node, not visited by traversal, graph is not connected
                return false;
        }
    }
    return true;

};



void Map::Validate(Map* map){
    if(CheckTerritoryBelongToOneContinent(map)){
        cout << "Each country belongs to one and only one continent"<<endl;
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

};






