#include "BidingFacility.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

BidingFacility::BidingFacility() {
    cout << "\nBidingFacility::BidingFacility()" << endl;
    // TO-DO: GET PLAYER LIST FROM GAME OBJECT

//    this->initialize();
}


void BidingFacility::initialize() {
    cout << "\nBidingFacility::initialize()" << endl;
    // TO-DO: GET PLAYER LIST FROM GAME OBJECT
}

void BidingFacility::initialize(string _players[], int _size) {
    cout << "\nBidingFacility::initialize()" << endl;

    // Invalid array size
    if(_size <= 0) {
        cout << "Initialize failed";
        return;
    }

    ifInitialized = true;

    // Show detail
    cout << "Number of player: " << to_string(_size) << endl;
    for (int i = 0; i < _size; i++){
        cout << "[" << i << "] " << _players[i] << endl;
        players.push_back(_players[i]);
    }
}

void BidingFacility::start() {
    cout << "\nBidingFacility::start()" << endl;

    // Return for not initialized error
    if(!ifInitialized){
        cout << "BidingFacility hasn't been initialized yet"; return;
    }

    string str = "";
    int playerNumber = players.size();
//    int playerNumber = 3;
    int bids[playerNumber];

    cout << "Number of player: " << playerNumber << "\n" << endl;

    // Initialize bid[]
    for (int i = 0; i < playerNumber; i++){
        bids[i] = 0;
        cout << "[" << i << "] " << players[i] <<", with bid: " << bids[i] << endl;
    }

    // INPUT BID
    int tempBid;
    for (int i = 0; i < playerNumber; i++){
        cout << "\n[" << i << "] " << players[i] <<"'s turn, place your bid" << endl;
        cout << "Your bid: ";
        cin >> tempBid;

        // Invalid input
        while(cin.fail() || tempBid < 0){
            cout << "Wrong number input, try again: ";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            cin >> tempBid;
        }

        cout << "Bid is hidden near the game board" << endl;
        bids[i] = tempBid;
    }

    cout << "\n\nBID REVEAL\n==========\n";
    for (int i = 0; i < playerNumber; i++){
        str = "[" + to_string(i) + "] " + players[i] + "'s bid: " +  to_string(bids[i]) + "\n";
        cout << str;

    }

    cout << "\nCALCULATING..." << endl;

    bool ifZero = true;
    bool ifTie = false;

    // CHECKING ALL ZERO
    for (int i = 0; i < playerNumber; i++){
        if(ifZero) if(bids[i] != 0) ifZero = false;
    }

    if(ifZero) resultLog += "ALL BIDS ARE ZERO, the player with an alphabetical last name order wins\n";

    // SELECTION SORT
    for (int i = 0; i < playerNumber; i++){

        int currentMaxBid = bids[i];
        string currentMaxPlayer = players[i];
        int currentMaxIndex = i;

//        cout << ">> " << i << "\ncurrentMaxBid\t\t" << currentMaxBid << "\ncurrentMaxPlayer\t" << currentMaxPlayer << endl;

        for (int j = i + 1; j < playerNumber; j++){
//            cout << "|-Comparing with\n|-players[j]\t\t" << players[j] << "\n|-bid[j]\t\t" << bids[j] << endl;
            if (currentMaxBid < bids[j]){
                currentMaxBid = bids[j];
                currentMaxPlayer = players[j];
                currentMaxIndex = j;
            } else if (currentMaxBid == bids[j]){
//                cout << "TIE on " << players[j] << " with " << currentMaxPlayer << endl;
                if(!ifZero && !ifTie){
                    resultLog += "TIE IN BIDS, player with an alphabetical last name order wins the bid\n";
                    ifTie = true;
                }
                if(currentMaxPlayer > players[j]){
                    currentMaxBid = bids[j];
                    currentMaxPlayer = players[j];
                    currentMaxIndex = j;
                }
            }
        }

        if (currentMaxIndex != i){
            bids[currentMaxIndex] = bids[i];
            players[currentMaxIndex] = players[i];
            bids[i] = currentMaxBid;
            players[i] = currentMaxPlayer;
        }
    }



    // RESULT

    for(int i = 0; i < players.size(); i++){
        resultLog +=  to_string(i+1) + "- " + players[i] + ":" + to_string(bids[i]) + "\n";
    }

    if(!ifZero) {
        resultLog += players[0] + " win the bid with " + to_string(bids[0]) + ".\n";
    } else {
        resultLog += players[0] + " win the bid.\n";
        resultLog += "The players will play in the order above.\n";
    }

}

void BidingFacility::getResultLog(){
    cout << "\nBidingFacility::getResultLog()" << endl;
    if(!ifInitialized) cout << "BidingFacility hasn't been initialized yet" << endl;
    else cout << resultLog << endl;
}

//int main(){
//
//    cout << "\nTesting Driver >> Biding Facility" << endl;
//
//    // {"Jack","Tim", "July", "Thierry"} {"Ngyuan", "Noah", "Chen"}
//    string players[3]  = {"Ngyuan", "Noah", "Chen"};
//    int size = sizeof(players)/sizeof(players[0]);
//
//    BidingFacility bf;
//    bf.initialize(players, size);
//    bf.start();
//    bf.getResultLog();
//
//    return 0;
//}