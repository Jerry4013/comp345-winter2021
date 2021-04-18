//
// Created by jerry on 3/30/2021.
//

#ifndef OBSERVER_SUBJECT_H
#define OBSERVER_SUBJECT_H
#include "Observer.h"
#include <list>
using namespace std;

class Subject {
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();

private:
    list<Observer*> *_observers;
};


#endif //OBSERVER_SUBJECT_H
