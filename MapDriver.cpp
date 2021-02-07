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
    Continent continent1 = Continent("Continent1" , 1);
    Continent continent2 =Continent("Continent2" , 2);
    Continent continent3 =Continent("Continent3" , 3);
    Continent continent4 =Continent("Continent4" , 4);
    Continent continent5 =Continent("Continent5" , 5);

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

    Territory T1 = Territory("Territory1",1,"continent1");
    Territory T2 = Territory("Territory2",2,"continent1");
    Territory T3 = Territory("Territory3",3,"continent2");
    Territory T4 = Territory("Territory4",4,"continent3");
    Territory T5 = Territory("Territory5",5,"continent4");
    Territory T6 = Territory("Territory6",6,"continent5");

    T1.GetNumTroops(1);
    T2.GetNumTroops(2);
    T3.GetNumTroops(3);
    T4.GetNumTroops(1);
    T5.GetNumTroops(2);
    T6.GetNumTroops(3);

    continent1.AddTerritory(&T1);
    continent1.AddTerritory(&T2);
    continent2.AddTerritory(&T3);
    continent3.AddTerritory(&T4);
    continent4.AddTerritory(&T5);
    continent5.AddTerritory(&T6);

    helper.AddEdgesCountry(1,2);
    helper.AddEdgesCountry(2,3);
    helper.AddEdgesCountry(3,4);
    helper.AddEdgesCountry(4,5);
    helper.AddEdgesCountry(5,6);
    helper.PrintTerritoryMatrix();

    testmap.Validate(&testmap);



}