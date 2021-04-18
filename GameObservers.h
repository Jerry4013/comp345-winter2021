//
// Created by jerry on 4/14/2021.
//

#ifndef COMP345_WINTER2021_GAMEOBSERVERS_H
#define COMP345_WINTER2021_GAMEOBSERVERS_H

#include "Observer.h"
#include "Game.h"

using namespace std;

class PhaseObserver : public Observer {
public:
    PhaseObserver();
    PhaseObserver(Game* game);
    ~PhaseObserver();
    void Update();
private:
    Game *_subject;
};

class StatisticsObserver : public Observer {
public:
    StatisticsObserver();
    StatisticsObserver(Game* game);
    ~StatisticsObserver();
    void Update();

private:
    Game *_subject;
};

#endif //COMP345_WINTER2021_GAMEOBSERVERS_H
