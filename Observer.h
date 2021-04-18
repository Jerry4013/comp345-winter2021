//
// Created by jerry on 3/30/2021.
//

#ifndef OBSERVER_OBSERVER_H
#define OBSERVER_OBSERVER_H


class Observer {
public:
    ~Observer();
    virtual void Update() = 0;

protected:
    Observer();
};


#endif //OBSERVER_OBSERVER_H
