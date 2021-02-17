//
// Created by Luojia yan on 2021-02-07.
//

#include "Map.h"
using namespace std;
#include "iostream"

int main() {
    Map testmap = Map("test");
    HelperFunctionMap helper;
    testmap.CreateCountryMatrix();
    testmap.CreateContinentMatrix();
    Continent continent1 = Continent("Continent0" , 0);
    Continent continent2 =Continent("Continent1" , 1);
    Continent continent3 =Continent("Continent2" , 2);
    Continent continent4 =Continent("Continent3" , 3);
    Continent continent5 =Continent("Continent4" , 4);

    testmap.AddContinent(&continent1);
    testmap.AddContinent(&continent2);
    testmap.AddContinent(&continent3);
    testmap.AddContinent(&continent4);
    testmap.AddContinent(&continent5);


    helper.AddEdgesContinents(1,2);
    helper.AddEdgesContinents(2,3);
    helper.AddEdgesContinents(3,4);
    helper.AddEdgesContinents(4,1);
    helper.AddEdgesContinents(1,3);
    helper.PrintContinentMatrix();

    Territory *T0 = new Territory("Territory1",0,0);
    Territory *T1 = new Territory("Territory2",1,0);
    Territory *T2 = new Territory("Territory3",2,1);
    Territory *T3 = new Territory("Territory4",3,2);
    Territory *T4 = new Territory("Territory5",4,3);
    Territory *T5 = new Territory("Territory6",5,4);

    T0->SetNumTroops("player1",1);
    T1->SetNumTroops("player2",2);
    T2->SetNumTroops("player3",3);
    T3->SetNumTroops("player4",4);

    T0->GetNumTroops("player1");
    T1->GetNumTroops("player2");
    T2->GetNumTroops("player3");
    T3->GetNumTroops("player4");
    T4->GetNumTroops("player1");
    T5->GetNumTroops("player2");

    continent1.AddTerritory(T0);
    continent1.AddTerritory(T1);
    continent2.AddTerritory(T2);
    continent3.AddTerritory(T3);
    continent4.AddTerritory(T4);
    continent5.AddTerritory(T5);

    helper.AddEdgesCountry(T0,T1);
    helper.AddEdgesCountry(T1,T2);
    helper.AddEdgesCountry(T2,T3);
    helper.AddEdgesCountry(T3,T4);
    helper.AddEdgesCountry(T4,T5);
    helper.PrintContinentMatrix();
    helper.PrintTerritoryMatrix();

    testmap.Validate(&testmap);



}
