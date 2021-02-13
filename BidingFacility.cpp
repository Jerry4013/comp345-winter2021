#include "BidingFacility.h"
#include "iostream"
#include <iomanip>
using namespace std;



class BidingFacility {
public:
    void start();
    void getBids();
    void getResultLog();
private:
    string players[3]  = {"Ngyuan", "Noah", "Chen"};
    string resultLog;
    void initialize();

    void initialize(string *_players, int _size);
};

void BidingFacility::initialize(string _players[], int _size) {
    cout << "BidingFacility::initialize()" << endl;
}

void BidingFacility::start() {
    cout << "BidingFacility::start()" << endl;

    int playerNumber = 3;
    cout << "Number of player: " << playerNumber << "\n" << endl;

    const int n = playerNumber;
    int bid[playerNumber];

    for (int i = 0; i < playerNumber; i++){
        bid[i] = 0;
        cout << "[" << i << "] " << players[i] <<", with bid: " << bid[i] << endl;
    }

    int tempBid;

    for (int i = 0; i < playerNumber; i++){
        cout << "\n[" << i << "] " << players[i] <<"'s turn" << endl;

        cout << "Place your bid!" << endl;
        cout << "Your bid: ";
        cin >> tempBid;
        while(cin.fail() || tempBid < 0){
            cout << "Wrong number input, try again: ";
            std::cin.clear();
            std::cin.ignore(256,'\n');
            cin >> tempBid;
        }
        cout << "Bid is hidden near the game board" << endl;
        bid[i] = tempBid;
    }

    // CHECKING ALL ZERO
    bool ifBidsNotZero = false;

    for (int i = 0; i < playerNumber; i++){
        tempBid = bid[i];
        if(!ifBidsNotZero) if(tempBid != 0) ifBidsNotZero = true;
    }

    if(!ifBidsNotZero){
        cout << "ALL BIDS ARE ZERO" << endl;
        cout << "END" << endl;
        return;
    }

    // SORTING
    for (int i = 0; i < playerNumber; i++){
        int currentMaxBid = bid[i];
        string currentMaxPlayer = players[i];
        int currentMaxIndex = i;

        for (int j = i + 1; j < playerNumber; j++){
            if (currentMaxBid < bid[j]){
                currentMaxBid = bid[j];
                currentMaxPlayer = players[j];
                currentMaxIndex = j;
            }
        }

        if (currentMaxIndex != i){
            bid[currentMaxIndex] = bid[i];
            players[currentMaxIndex] = players[i];
            bid[i] = currentMaxBid;
            players[i] = currentMaxPlayer;
        }
    }

    for (int i = 0; i < playerNumber; i++){
        cout << "[" << i << "] " << players[i] << "'s bid: " << bid[i] << endl;
    }

    string tempS = "";

    cout << "\nBID REVEAL\n=========================\n";
    for (int i = 0; i < playerNumber; i++){
        cout << "[" << i << "] " << players[i] << "'s bid: " << bid[i] << endl;
        resultLog +=  "[" + to_string(i) + "] " + players[i] + "'s bid: " +  to_string(bid[i]) + "\n";
    }

    resultLog += players[0] + " win the bid with " + to_string(bid[0]) + ".\n";
    cout << players[0] << " win the bid with " << bid[0] << "." << endl;

//    cout << resultLog;
}

//int BidingFacility::getPlayerNumber(string arr[]) {
////    cout << "BidingFacility::getPlayerNumber()" << "\n";
//    return sizeof(arr) / sizeof(*arr);
//}

void BidingFacility::getResultLog(){
    cout << "BidingFacility::getResultLog()" << "\n";
    cout << resultLog + "\n";
}

void BidingFacility::getBids(){
    //    cout << "BidingFacility::getBids()" << "\n";
}



int main(){

    cout << "Testing Driver >> Biding Facility\n";

    string players[3]  = {"Ngyuan", "Noah", "Chen"};
    int size = sizeof(players)/sizeof(players[0]);
    cout << size << endl;



    BidingFacility bf;
//    bf.initialize(players, size);
    bf.start();
    bf.getResultLog();

    return 0;
}