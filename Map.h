//
// Created by Luojia yan on 2020-11-21.
//
#pragma once

#include <string>
#include <vector>
#include <list>
#include <queue>
using namespace std;
class Territory {
public:
    int TerritoryNumber;
    std::string TerritoryName;
    int NumberOfTroops;
    std::string OwnerName;
    std::string ContinentName;
    int ContinentNum;

    //constructor
    Territory();
    ~Territory();
    Territory(int TerritoryNumber,std::string TerritoryName,int NumberOfTroops,std::string OwnerName,int ContinentNum,
            std::string ContinentName);

    //getter
    int GetTerritoryNumber();
    string GetTerritoryName();
    int GetNumOfTroops();
    string GetOwnererName();
    int GetContinentNumber();
    string GetContinentName();

    //setter
    void SetTerritoryNumber(int TerritoryNumber);
    void SetTerritoryName(string TerritoryName);
    void SetNumOfTroops(int NumOfTroops);
    void SetOwnerName(string OwnerName);
    void SetContinentNumber(int ContinentNumber);
    void SetContinentName(string ContinentName);

    //check if two territory is neighbor
    bool IsNeighbor(Territory* territory1,Territory* territory2,int Matrix[100][100]);

    //validate territory
    void validate(Territory* territory);


};
class Continent{
public:
    std::string Continetname;
    int ContinentNum;
    int BonusValue;
    std::vector<Territory*> territories;

    Continent();
    ~Continent();
    Continent(int ContinentNum,std::string Continetname,int BonusValue,std::vector<Territory*> territories);

    //getter
    int GetContinentNum();
    std::string GetContinentName();
    int GetBonusNum();
    std::vector<Territory*> ReturnTerritory();
    //setter
    void SetContinentNum(int Continentnum);
    void SetContinentName(string Continentname);
    void SetBonusNum(int BonusNumber);
    void AddTerritory(Territory* territory);
    void RemoveTerritory(std::vector<Territory*> territories,int TerritoryNum);

    //Occupied By one player
    bool OccupiedByOnePlayer();


    //Validation
    void validateContinent(Continent* continent);

};

