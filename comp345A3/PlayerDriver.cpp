//
// Created by CMY on 2020-11-27.
//

//#include "Player.h"
//
//int main() {
//
//
//    //Territories generations
//    Territory* USA =new Territory(1,"USA", 10, "player1",0,"NA");
//    Territory* Canada =new Territory(2,"Canada", 10, "player2",0,"NA");
//    Territory* Mexico =new Territory(3,"Mexico", 10, "player1",0,"NA");
//    Territory* Cuba =new Territory(4,"Cuba", 10, "player2",0,"NA");
//    Territory* Brazil =new Territory(5,"Brazil", 10, "none",0,"NA");
//    Territory* Argentina =new Territory(6,"Argentina", 10, "none",0,"NA");
//
//    vector<Territory*> TerritoryList;
//    TerritoryList.push_back(USA);
//    TerritoryList.push_back(Canada);
//    TerritoryList.push_back(Mexico);
//    TerritoryList.push_back(Cuba);
//    TerritoryList.push_back(Brazil);
//    TerritoryList.push_back(Argentina);
//    Continent continent = Continent(0, "NA", 2, TerritoryList);
//
//    vector<Territory*> player1list;
//    vector<Territory*> player2list;
//
////    player1list.push_back(USA);
////    player1list.push_back(Mexico);
////    player1list.push_back(Canada);
////    player1list.push_back(Cuba);
////    player1list.push_back(Brazil);
////    player1list.push_back(Argentina);
////    Hand* player1hand = new Hand(Card(bomb));
////    Hand* player2hand = new Hand();
//
//    //Test for Player's constructor
//    Player* player1;
//    Player* player2;
//    player1 =new Player("player1",player1list);
//    player2 =new Player("player2",player2list);
//    vector<Player*> PlayerList;
//
//    PlayerList.push_back(player1);
//    PlayerList.push_back(player2);
//
//    PlayerList[0]->addTerritory(USA);
//    PlayerList[0]->addTerritory(Mexico);
//    PlayerList[0]->addTerritory(Canada);
//    PlayerList[0]->addTerritory(Cuba);
//    PlayerList[0]->addTerritory(Brazil);
//    PlayerList[0]->addTerritory(Argentina);
//
//
//
//    //Test for Player's member methods
//    {
//        //Test for getters
////        cout << "\n---------- Getters -----------" << endl;
////        cout << "getPlayerName(): " << player1->getPlayerName() << endl;
////        cout << "getReinforcementPool(): " << player1->getReinforcementPool() << endl;
////        cout << "getOwnedTerritories(): " << player1->getOwnedTerritories() << endl;
////        cout << "getHand(): ";
//////    for (int i = 0; i <  player1->getHand().getHandVector()->size(); i++) {
//////        cout << player1->getHand().getHandVector()[i].getCardType() << ", " ;
//////    }
////        cout << "Unavailable, need to fix. <====" << endl;
////        cout << "getOrdersList(): ";
////        for (int i = 0; i <  player1->getOrdersList().size(); i++) {
////            cout << player1->getOrdersList()[i]->getType() << ", " ;
////        }
////        cout << endl;
////        cout << "getTerritoryList(): " << player2->getOwnedTerritories() << endl;
////        for (int i = 0; i <  player1->getTerritoryList().size(); i++) {
////            cout << player1->getTerritoryList()[i]->GetTerritoryName() << ", " ;
////        }
////        cout << endl;
////
////        //Test for setters
////        cout << "\n---------- Setters -----------" << endl;
////        player2->setPlayerName("Player2_for_testing");
////        cout << "setPlayerName(\"Player2_for_testing\"): " << player2->getPlayerName() << endl;
////        player2->setReinforcementPool(50);
////        cout << "setReinforcementPool(50): " << player2->getReinforcementPool() << endl;
////        vector<Territory*> player2NewList;
////        player2NewList.push_back(Cuba);
////        player2NewList.push_back(Brazil);
////        player2->setTerritoryList(player2NewList);
////        cout << "setOwnedTerritories(): ";
////        for (int i = 0; i <  player2->getTerritoryList().size(); i++) {
////            cout << player2->getTerritoryList()[i]->GetTerritoryName() << ", " ;
////        }
////        cout << endl;
////
////        //Test for reinforcement pool
////        cout << "\n---------- Reinforcement Pool -----------" << endl;
////        player2->addArmiesToReinforcementPool(10);
////        cout << "addArmiesToReinforcementPool(10): " << player2->getReinforcementPool() << endl;
////        player2->TakeArmiesFromReinforcementPool(20);
////        cout << "TakeArmiesFromReinforcementPool(20): " << player2->getReinforcementPool() << endl;
////
////        //Test for territory
////        cout << "\n---------- Territory -----------" << endl;
////        player2->addTerritory(Argentina);
////        cout << "addTerritory(Argentina): " << player2->getOwnedTerritories() << endl;
////        for (int i = 0; i <  player2->getTerritoryList().size(); i++) {
////            cout << player2->getTerritoryList()[i]->GetTerritoryName() << ", " ;
////        }
////        cout << endl;
////        player2->removeTerritory(Cuba);
////        cout << "removeTerritory(Cuba): " << player2->getOwnedTerritories() << endl;
////        for (int i = 0; i <  player2->getTerritoryList().size(); i++) {
////            cout << player2->getTerritoryList()[i]->GetTerritoryName() << ", " ;
////        }
////        cout << endl;
////        cout << "toAttack(): ";
//////    for (int i = 0; i <  player2->toAttack().size(); i++) {
//////        cout << player2->toAttack()[i]->GetTerritoryName() << ", " ;
//////    }
////        cout << "Unavailable, need to fix. <====" << endl;
////        cout << "toDefend(): ";
////        for (int i = 0; i <  player2->toDefend().size(); i++) {
////            cout << player2->toDefend()[i]->GetTerritoryName() << ", " ;
////        }
////        cout << endl;
//
//    }
//
//    //Test for order issuing and order execution
//    cout << "\n---------- Orders -----------" << endl;
//    vector<Territory *> player2OrdersList;
//    PlayerList[0]->issueOrder(new Deploy());
//    PlayerList[0]->issueOrder(new Bomb());
//    PlayerList[0]->issueOrder(new Blockade());
//    PlayerList[1]->issueOrder(new Deploy());
//    PlayerList[0]->issueOrder(new Bomb());
//    PlayerList[1]->issueOrder(new Deploy());
//    PlayerList[1]->issueOrder(new Airlift());
//    PlayerList[0]->issueOrder(new Negotiate());
//    PlayerList[1]->issueOrder(new Advance());
//    PlayerList[1]->issueOrder(new Negotiate());
//    cout << "P1 issueOrder(): ";
//    for (int i = 0; i < PlayerList[0]->getOrdersList().size(); i++) {
//        cout << PlayerList[0]->getOrdersList()[i]->getType() << ", ";
//    }
//    cout << endl;
//    cout << "P2 issueOrder(): ";
//    for (int i = 0; i < PlayerList[1]->getOrdersList().size(); i++) {
//        cout << PlayerList[1]->getOrdersList()[i]->getType() << ", ";
//    }
//    cout << endl;
//
//    //Test for Order Execution Phase
//    //finding the max number of orders from one ordersList
//    int maxOrderNum = 0;
//    for (int i = 0; i < PlayerList.size(); i++) {
//        if (maxOrderNum < PlayerList[i]->getOrdersList().size()) {
//            maxOrderNum = PlayerList[i]->getOrdersList().size();
//        }
//    }
//
//    cout << "\n>>>>> Priority orders <<<<< \n    maximum of order -> " << maxOrderNum << "\n";
//    //find and execute every player's deploy
//    for (int i = 0; i < PlayerList.size(); i++) {
//        cout << "Deploy of " << PlayerList[i]->getPlayerName() << ": \n";
//        for (int j = 0; j < PlayerList[i]->getOrdersList().size(); j++) {
//            if (PlayerList[i]->getOrdersList()[j]->getType() == "Deploy") {
//                cout << "\tOrder #" << j << " >>> ";
//                PlayerList[i]->getOrdersList()[j]->execute();
//            } else { cout << "\tOrder #" << j << " pass" << endl; }
//        }
//    }
//    //find and execute player's airlift
//    for (int i = 0; i < PlayerList.size(); i++) {
//        cout << "Airlift of " << PlayerList[i]->getPlayerName() << ": \n";
//        for (int j = 0; j < PlayerList[i]->getOrdersList().size(); j++) {
//            if (PlayerList[i]->getOrdersList()[j]->getType() == "Airlift") {
//                cout << "\tOrder #" << j << " >>> ";
//                PlayerList[i]->getOrdersList()[j]->execute();
//                break;
//            } else { cout << "\tOrder #" << j << " pass" << endl; }
//        }
//    }
//    //find and execute player's blockade
//    for (int i = 0; i < PlayerList.size(); i++) {
//        cout << "Blockade of " << PlayerList[i]->getPlayerName() << ": \n";
//        for (int j = 0; j < PlayerList[i]->getOrdersList().size(); j++) {
//            if (PlayerList[i]->getOrdersList()[j]->getType() == "Blockade") {
//                cout << "\tOrder #" << j << " >>> ";
//                PlayerList[i]->getOrdersList()[j]->execute();
//                break;
//            } else { cout << "\tOrder #" << j << " pass" << endl; }
//        }
//    }
//
//    cout << ">>>>> Non-priority orders <<<<< \n";
//    //execute other orders in round robin fashion
//    for (int i = 0; i < PlayerList.size(); i++) {
//        for (int j = 0; j < maxOrderNum; j++) {
//
//            if (PlayerList[i]->getOrdersList()[j]->getType() == "Bomb" ||
//                PlayerList[i]->getOrdersList()[j]->getType() == "Advance" ||
//                PlayerList[i]->getOrdersList()[j]->getType() == "Negotiate") {
//                cout << PlayerList[i]->getPlayerName() << "\tOrder #" << j << " >>> ";
//                PlayerList[i]->getOrdersList()[j]->execute();
//            } else { cout << PlayerList[i]->getPlayerName() << "\tOrder #" << j << " pass" << endl; }
//
//        }
//    }
//
//        //clear each player's ordersList for this round
//        for (int i = 0; i < PlayerList.size(); i++) {
//            PlayerList[i]->player_ordersList.clear();
//        }
////        cout << "P1 Order List should be empty: ";
////        for (int i = 0; i < PlayerList[0]->getOrdersList().size(); i++) {
////            cout << PlayerList[0]->getOrdersList()[i]->getType() << ", ";
////        }
////        cout << endl;
////        cout << "P2 Order List should be empty: ";
////        for (int i = 0; i < PlayerList[1]->getOrdersList().size(); i++) {
////            cout << PlayerList[1]->getOrdersList()[i]->getType() << ", ";
////        }
//        cout << endl;
//
//
//
//
//    //Test for winning & losing condition check
//    cout << "\n---------- Winning Check -----------" << endl;
//
//    Player* winner;
//    //win condition
//    for (int i = 0; i < PlayerList.size(); i++) { //for each player
//        int terrCount = 0;
//        for (int j = 0; j < TerritoryList.size(); j++) { // for each territory
//            if (PlayerList[i]->getPlayerName() != TerritoryList[j]->GetOwnererName()) {
//                cout << PlayerList[i]->getPlayerName() << " is not the winner," << " he has " << terrCount << " out of " << TerritoryList.size() << " territory(s).\n";
//                break;
//            } else { terrCount++;}
//            if (terrCount == TerritoryList.size()) {
//                winner = PlayerList[i];
//                cout << winner->getPlayerName()+ " is the winner," << " he has " << terrCount << " out of " << TerritoryList.size() << " territory(s).\n";
//            }
//        }
//    }
//    //lose condition
//    for (int i = 0; i < PlayerList.size(); i++) { //for each player
//        int terrCount = 0;
//        for (int j = 0; j < TerritoryList.size(); j++) { // for each territory
//            if (PlayerList[i]->getPlayerName() == TerritoryList[j]->GetOwnererName()) {
//                cout << PlayerList[i]->getPlayerName() << " has not been defeated yet," << " he has lost " << terrCount << " out of " << TerritoryList.size() << " territory(s).\n";
//                break;
//            } else { terrCount++;}
//            if (terrCount == TerritoryList.size()) {
//                cout << PlayerList[i]->getPlayerName()+ " has been defeated," << " he does not have " << terrCount << " out of " << TerritoryList.size() << " territory(s).\n";
//            }
//        }
//    }
//
//    return 0;
//};
