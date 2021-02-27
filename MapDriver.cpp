//
// Created by Luojia yan on 2021-02-07.
//

#include "Map.h"
using namespace std;
#include "iostream"
#include "MapDriver.h"

int mapDriver::main() {
    Map testMap = Map("test", 6, 7);
    Continent continent1 = Continent("Continent1" , 1);
    Continent continent2 = Continent("Continent2" , 2);
    Continent continent3 = Continent("Continent3" , 3);
    Continent continent4 = Continent("Continent4" , 4);
    Continent continent5 = Continent("Continent5" , 5);
    Continent continent6 = Continent("Continent6" , 6);

    testMap.AddContinent(&continent1);
    testMap.AddContinent(&continent2);
    testMap.AddContinent(&continent3);
    testMap.AddContinent(&continent4);
    testMap.AddContinent(&continent5);
    testMap.AddContinent(&continent6);

    /*
    helper.AddEdgesContinents(1,2);
    helper.AddEdgesContinents(2,3);
    helper.AddEdgesContinents(3,4);
    helper.AddEdgesContinents(4,1);
    helper.AddEdgesContinents(1,3);
     */


    Territory *T0 = new Territory("Territory1",1,1);
    Territory *T1 = new Territory("Territory2",2,1);
    Territory *T2 = new Territory("Territory3",3,2);
    Territory *T3 = new Territory("Territory4",4,3);
    Territory *T4 = new Territory("Territory5",5,4);
    Territory *T5 = new Territory("Territory6",6,5);
    Territory *T6 = new Territory("Territory7",7,6);

    T0->SetNumTroops("player1",1);
    T1->SetNumTroops("player2",2);
    T2->SetNumTroops("player3",3);
    T3->SetNumTroops("player4",4);

    T0->getArmiesOfPlayer("player1");
    T1->getArmiesOfPlayer("player2");
    T2->getArmiesOfPlayer("player3");
    T3->getArmiesOfPlayer("player4");
    T4->getArmiesOfPlayer("player1");
    T5->getArmiesOfPlayer("player2");
    T6->getArmiesOfPlayer("player3");

    continent1.AddTerritory(T0);
    continent1.AddTerritory(T1);
    continent2.AddTerritory(T2);
    continent3.AddTerritory(T3);
    continent4.AddTerritory(T4);
    continent5.AddTerritory(T5);
    continent6.AddTerritory(T6);

    testMap.addEdgesTerritory(T0, T1);
    testMap.addEdgesTerritory(T1, T0);
    testMap.addEdgesTerritory(T1, T2);
    testMap.addEdgesTerritory(T2, T1);
    testMap.addEdgesTerritory(T2, T3);
    testMap.addEdgesTerritory(T3, T2);
    testMap.addEdgesTerritory(T3, T4);
    testMap.addEdgesTerritory(T4, T3);
    testMap.addEdgesTerritory(T4, T5);
    testMap.addEdgesTerritory(T5, T4);
    testMap.addEdgesTerritory(T5, T6);
    testMap.addEdgesTerritory(T6, T5);

    testMap.PrintContinentMatrix();
    testMap.PrintTerritoryMatrix();

//    testMap.validate(&testMap);
    testMap.dfsValidate();
    
    Map testMap2 = Map("test", 6, 7);
    Continent continent1_2 = Continent("Continent1" , 1);
    Continent continent2_2= Continent("Continent2" , 2);
    Continent continent3_2 = Continent("Continent3" , 3);
    Continent continent4_2 = Continent("Continent4" , 4);
    Continent continent5_2 = Continent("Continent5" , 5);
    Continent continent6_2 = Continent("Continent6" , 6);
    
    testMap2.AddContinent(&continent1_2);
    testMap2.AddContinent(&continent2_2);
    testMap2.AddContinent(&continent3_2);
    testMap2.AddContinent(&continent4_2);
    testMap2.AddContinent(&continent5_2);
    testMap2.AddContinent(&continent6_2);
    
    Territory *T0_2 = new Territory("Territory1",1,1);
    Territory *T1_2 = new Territory("Territory2",2,1);
    Territory *T2_2 = new Territory("Territory3",3,2);
    Territory *T3_2 = new Territory("Territory4",4,3);
    Territory *T4_2 = new Territory("Territory5",5,4);
    Territory *T5_2 = new Territory("Territory6",6,5);
    Territory *T6_2 = new Territory("Territory7",7,6);
    
    T0_2->SetNumTroops("player1",1);
    T1_2->SetNumTroops("player2",2);
    T2_2->SetNumTroops("player3",3);
    T3_2->SetNumTroops("player4",4);

    T0_2->getArmiesOfPlayer("player1");
    T1_2->getArmiesOfPlayer("player2");
    T2_2->getArmiesOfPlayer("player3");
    T3_2->getArmiesOfPlayer("player4");
    T4_2->getArmiesOfPlayer("player1");
    T5_2->getArmiesOfPlayer("player2");
    T6_2->getArmiesOfPlayer("player3");
    
    continent1_2.AddTerritory(T0_2);
    continent1_2.AddTerritory(T1_2);
    continent2_2.AddTerritory(T2_2);
    continent3_2.AddTerritory(T3_2);
    continent4_2.AddTerritory(T4_2);
    continent5_2.AddTerritory(T5_2);
    continent6_2.AddTerritory(T6_2);

    testMap2.addEdgesTerritory(T0_2, T1_2);
    testMap2.addEdgesTerritory(T1_2, T0_2);
    testMap2.addEdgesTerritory(T1_2, T2_2);
    testMap2.addEdgesTerritory(T2_2, T1_2);
    testMap2.addEdgesTerritory(T4_2, T5_2);
    testMap2.addEdgesTerritory(T5_2, T4_2);
    testMap2.addEdgesTerritory(T5_2, T6_2);
    testMap2.addEdgesTerritory(T6_2, T5_2);
    
    testMap2.PrintContinentMatrix();
    testMap2.PrintTerritoryMatrix();
    
    //    testMap.validate(&testMap);
    testMap2.dfsValidate();
    return 0;

}
