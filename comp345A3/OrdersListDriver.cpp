//#include <string>
//#include <iostream>
//
//#include "Map.h"
//#include "OrdersLists.h"
//
//
//int main() {
//
//    // Create some players and territories to do the tests
////    Player player = Player();
////    Player opponent =  Player();
//    Continent continent = Continent("NA",1);
//    Territory USA = Territory("USA", 1, 0, "player","na");
//    Territory Canada = Territory("Canada", 2, 0, "opponent","na");
//    continent.AddTerritory(USA);
//    continent.AddTerritory(Canada);
//
//
//    // Test the orders
//    std::cout << "Testing the orders:" << std::endl << std::endl;
//    Order* deploy = new Deploy();
//    Order* advance = new Advance();
//    Order* bomb = new Bomb();
//    Order* blockade = new Blockade();
//    Order* negotiate = new Negotiate();
//    Order* airlift = new Airlift();
//
//    std::cout << "Deploy is valid: " << deploy->validate() << std::endl;
//    deploy->execute();
//    std::cout << "Advance is valid: " << advance->validate() << std::endl;
//    advance->execute();
//    std::cout << "Bomb is valid: " << bomb->validate() << std::endl;
//    bomb->execute();
//    std::cout << "Blockade is valid: " << blockade->validate() << std::endl;
//    blockade->execute();
//    std::cout << "Negotiate is valid: " << negotiate->validate() << std::endl;
//    negotiate->execute();
//    std::cout << "Airlift is valid: " << airlift->validate() << std::endl;
//    airlift->execute();
//
//    // Test the orders list
//    std::cout << std::endl
//              << "===" << std::endl
//              << std::endl
//              << "Testing the orders list" << std::endl;
//
//    OrdersList* ordersList = new OrdersList();
//    ordersList->queue(deploy);
//    ordersList->queue(advance);
//    ordersList->queue(bomb);
//    ordersList->queue(blockade);
//    ordersList->queue(negotiate);
//    ordersList->queue(airlift);
//
//    std::cout << *ordersList << std::endl;
//
//    // Move orders within the list
//    // Expected after move: Bomb, Advance, Deploy, Negotiate, Blockade, Airlift
//    ordersList->move(1, 4);
//    ordersList->move(3, 5);
//    ordersList->move(2, 1);
//
//    std::cout << *ordersList << std::endl;
//
//    // Remove orders
//    // Expected: Bomb, Deploy, Negotiate, Blockade
//    ordersList->deletes(2);
//    ordersList->deletes(5);
//
//    std::cout << *ordersList << std::endl;
//
//    ordersList = NULL;
//    deploy = NULL;
//    advance = NULL;
//    bomb = NULL;
//    airlift = NULL;
//    blockade = NULL;
//    negotiate = NULL;
//    delete ordersList;
//    delete deploy;
//    delete advance;
//    delete bomb;
//    delete airlift;
//    delete blockade;
//    delete negotiate;
//
//
//    return 0;
//}