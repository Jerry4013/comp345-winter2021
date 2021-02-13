#include <iostream>
#include "Player.h"
#include <string>
using namespace std;

int main() {
    Player player;
    string newName = "ABC";
    player.setName(newName);
    cout << player.getTerritories().size();
    return 0;
}