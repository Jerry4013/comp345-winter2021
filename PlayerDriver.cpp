#include <iostream>
#include <vector>
#include "Player.h"
#include <string>
#include "PlayerDriver.h"

using namespace std;

int player::main() {
  
//    // Test Constructors
//    cout << endl << "Test Constructors:" << endl << "------------------------------------------------" << endl;
//    Player defaultPlayer;
//    cout << "A default player is created: " << endl << defaultPlayer << endl << endl;
//    string name;
//    int biding;
//    int coinSupply;
//    Territory territory1("territory1", 1, 1);
//    Territory territory2("territory2", 2, 2);
//    cout << "Enter player firstName: ";
//    cin >> name;
//    cout << "Enter biding coinSupply: ";
//    cin >> biding;
//    cout << "Enter initial coinSupply: ";
//    cin >> coinSupply;
//    vector<Territory*> territories;
//    territories.push_back(&territory1);
//    territories.push_back(&territory2);
//    Player userCreatedPlayer(name, biding, coinSupply, territories);
//    cout << "A customized player is created: " << endl << userCreatedPlayer.toString() << endl << endl;
//    Player player1(userCreatedPlayer);
//    cout << "player1 is created by copy constructor. firstName is " + player1.getName() << endl;
//    Player player2;
//    player2 = player1;
//    cout << "player2 is created by assignment operator. firstName is " + player2.getName() << endl;
//    cout << "Print this player with stream insertion: " << endl;
//    cout << player2 << endl;
//
//    // Test features:
//    // 1. Player owns a collection of regions/countries
//    cout << endl << "Test Features:" << endl << "------------------------------------------------" << endl;
//    cout << "Player2 owns a collection of regions: " << endl;
//    vector<Territory *> territoriesOfPlayer2 = player2.getTerritories();
//    for (int i = 0; i < territoriesOfPlayer2.size(); i++) {
//        cout << *territoriesOfPlayer2[i] << endl;
//    }
//
//    // 2. Player owns a hand game cards
//    cout << endl << "Let's give player1 a card." << endl;
//    vector<Card*> cards;
//    Card lake(emptyKind, "Lake", 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
//              false,true, false, false, false, false, true, 0);
//    cards.push_back(&lake);
//    player1.setCards(cards);
//    cout << "Player1 has a card:" << endl;
//    vector<Card *> cardsOfPlayer1 = player1.getCards();
//    for (int i = 0; i < cardsOfPlayer1.size(); ++i) {
//        cout << * cardsOfPlayer1[i] << endl;
//    }
//
//    // 3. Player2 has his own biding facility object (see Part 5)
//    cout << endl << "Player2 has his own biding facility object: " << player2.getBiding() << endl;
//
//    // 4. PayCoin(), PlaceNewArmies(), MoveArmies(), MoveOverLand(). BuildCity(), and DestroyArmy().
//    cout << endl << "Player2 has coinSupply: " << player2.getCoins() << endl;
//    cout << endl << "Player2 can pay 2 coinSupply: " << endl;
//    player2.PayCoin(2);
//    cout << endl << "After payment, player2 has coinSupply: " << player2.getCoins() << endl;
//
//    cout << endl << "Player2 can place 2 new armies on territory 1: " << endl;
//    player2.PlaceNewArmies(2, territory1);
//    cout << territory1 << endl;
//
//    cout << endl << "Player2 can move armies: " << endl;
//    player2.MoveArmies(1, territory1, territory2);
//
//    cout << endl << "Player2 can move armies overLand: " << endl;
//    player2.MoveOverLand(1, territory2, territory1);
//
//    cout << endl << "Player2 can destroy armies: " << endl;
//    player2.DestroyArmy(1, player1, territory1);

    return 0;
}

