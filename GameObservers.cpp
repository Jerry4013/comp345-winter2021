//
// Created by jerry on 4/14/2021.
//
#include <iostream>
#include "GameObservers.h"

using namespace std;

PhaseObserver::PhaseObserver(Game *pGame) {
    _subject = pGame;
    _subject->Attach(this);
}

PhaseObserver::~PhaseObserver() {
    _subject->Detach(this);
}

void PhaseObserver::Update() {
    Player* currentPlayer = _subject->getCurrentPlayer();
    int cardIndex = _subject->getCardIndex();
    cout << "Phase Observer: " << endl;
    cout << "It's player " << currentPlayer->getId() << "'s turn. " << endl;
    cout << "Player " << currentPlayer->getId() << " selected card " << cardIndex << endl;
    cout << "He paid " << Hand::CARD_COSTS[cardIndex] << " coins." << endl;
    cout << *currentPlayer << endl;
}

PhaseObserver::PhaseObserver() {

}

StatisticsObserver::StatisticsObserver(Game *game) {
    _subject = game;
    _subject->Attach(this);
}

StatisticsObserver::~StatisticsObserver() {
    _subject->Detach(this);
}

void StatisticsObserver::Update() {
    Map* currentMap = _subject->getMap();
    currentMap->printForce(_subject->getNumOfPlayers());
    if (_subject->isGameEnd()) {
        _subject->computeScore();
        _subject->claimWinner();
    }
}

StatisticsObserver::StatisticsObserver() {

}



