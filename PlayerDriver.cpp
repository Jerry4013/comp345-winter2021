#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <string>

using namespace std;

int main() {
    Player player;
    string newName = "ABC";
    player.setName(newName);
    cout << player.getTerritories().size() << endl;

    Player player1;
    Player player2;
    player1.setName("player1");
    player2.setName("player2");
    cout << player1.getName() << endl;
    cout << player2.getName() << endl;
    player1 = player2;
    cout << player1 << endl;
    return 0;
}