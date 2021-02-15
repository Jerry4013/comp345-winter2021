#include <iostream>
#include <vector>
#include "Player.h"
#include <string>

using namespace std;

int main() {

    // Test Constructors
    cout << endl << "Test Constructors:" << endl << "------------------------------------------------" << endl;
    Player defaultPlayer;
    cout << "A default player is created: " << endl << defaultPlayer << endl << endl;
    string name;
    int biding;
    int coins;
    Territory territory1("territory1", 1, 1);
    Territory territory2("territory2", 2, 2);
    cout << "Enter player name: ";
    cin >> name;
    cout << "Enter biding coins: ";
    cin >> biding;
    cout << "Enter initial coins: ";
    cin >> coins;
    vector<Territory*> territories;
    territories.push_back(&territory1);
    territories.push_back(&territory2);
    Player userCreatedPlayer(name, biding, coins, territories);
    cout << "A customized player is created: " << endl << userCreatedPlayer.toString() << endl << endl;
    Player player1(userCreatedPlayer);
    cout << "player1 is created by copy constructor. name is " + player1.getName() << endl;
    Player player2;
    player2 = player1;
    cout << "player2 is created by assignment operator. name is " + player2.getName() << endl;
    cout << "Print this player with stream insertion: " << endl;
    cout << player2 << endl;

    // Test features:
    cout << endl << "Test Features:" << endl << "------------------------------------------------" << endl;
    cout << "Player2 owns a collection of regions: " << endl;
    vector<Territory *> territoriesOfPlayer2 = player2.getTerritories();
    for (int i = 0; i < territoriesOfPlayer2.size(); i++) {
        cout << *territoriesOfPlayer2[i] << endl;
    }

    cout << endl << "Player2 has his own biding facility object: " << player2.getBiding() << endl;
    // TODO: owns some cards
    cout << endl << "Player2 can pay 2 coins: " << endl;
    player2.PayCoin(2);
    cout << endl << "Player2 can place 2 new armies on territory 1: " << endl;
    player2.PlaceNewArmies(2, territory1);
    cout << territory1 << endl;

    // TODO: MoveArmies(), MoveOverLand(). BuildCity(), and DestroyArmy()

    return 0;
}