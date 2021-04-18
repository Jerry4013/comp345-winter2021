//
// Created by jerry on 4/14/2021.
//

#ifndef COMP345_WINTER2021_GAMEOBSERVERS_H
#define COMP345_WINTER2021_GAMEOBSERVERS_H

#include "Observer.h"
#include "GameEngine.h"

using namespace std;

class PhaseObserver : public Observer {
public:
    PhaseObserver();
    PhaseObserver(GameEngine* game);
    ~PhaseObserver();
    void Update();
private:
    GameEngine *_subject;
};

class StatisticsObserver : public Observer {
public:
    StatisticsObserver();
    StatisticsObserver(GameEngine* game);
    ~StatisticsObserver();
    void Update();

private:
    GameEngine *_subject;
};

#endif //COMP345_WINTER2021_GAMEOBSERVERS_H
