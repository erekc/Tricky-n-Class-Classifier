#ifndef WALKER_H
#define WALKER_H

#include <iostream>

class Walker
{
public:
    Walker();
    virtual void walk();
    virtual void reset();
    int* getCurrentPoint() { return this->currentPoint; };
    int getSteps() { return this->steps; };
    void printCurrentPoint();
private:
    int currentPoint[2] = {0, 0};
    int steps = 0;
};

#endif // WALKER_H
