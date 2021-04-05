//
// Created by jerry on 4/3/2021.
//

#include "PlayerStrategies.h"

int HumanStrategy::selectCard(Hand *hand, int coins) {
    int cardIndex;
    while (true) {
        cout << "Please select a card index (1-6) (You have " << coins << " coins):" << endl;
        cout << ">> ";
        cin >> cardIndex;
        cardIndex--;
        if (cardIndex < 0 || cardIndex >= Hand::CARD_COSTS_SIZE) {
            cout << "ERROR! Please enter a number from range 1-6!" << endl;
            cout << "Try again." << endl;
            continue;
        }
        if (coins < Hand::CARD_COSTS[cardIndex]) {
            cout << "ERROR! You don't have enough coin to buy this card!" << endl;
            cout << "Try again." << endl;
            continue;
        }
        break;
    }
    return cardIndex;
}

string HumanStrategy::toString() {
    return "Human Strategy";
}

int GreedyComputerStrategy::selectCard(Hand *hand, int coins) {
    for (int cardIndex = 0; cardIndex < hand->getHandCards().size(); ++cardIndex) {
        for (int j = 0; j < hand->getHandCards()[cardIndex]->getActions().size(); ++j) {
            ActionType actionType = hand->getHandCards()[cardIndex]->getActions()[j].actionType;
            if (actionType == ActionType::buildCity || actionType == ActionType::destroyArmy) {
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "The greedy computer selected card " << cardIndex + 1 << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                return cardIndex;
            }
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "No card can build a city or destroy an army. " << endl;
    cout << "The greedy computer selected card 1 by default." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    return 0;
}

string GreedyComputerStrategy::toString() {
    return "Greedy Computer Strategy";
}

int ModerateComputerStrategy::selectCard(Hand *hand, int coins) {
    for (int cardIndex = 0; cardIndex < hand->getHandCards().size(); ++cardIndex) {
        for (int j = 0; j < hand->getHandCards()[cardIndex]->getActions().size(); ++j) {
            ActionType actionType = hand->getHandCards()[cardIndex]->getActions()[j].actionType;
            if (actionType == ActionType::moveArmy || actionType == ActionType::placeArmy) {
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "The moderate computer selected card " << cardIndex + 1 << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                return cardIndex;
            }
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "No card can move an army or place an army. " << endl;
    cout << "The moderate computer selected card 1 by default." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    return 0;
}

string ModerateComputerStrategy::toString() {
    return "Moderate Computer Strategy";
}
