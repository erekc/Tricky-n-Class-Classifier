#ifndef WALKER_H
#define WALKER_H

#include <iostream>
#include <string>

class Walker
{
public:
    virtual void walk();
    virtual void reset();
    int* getCurrentPoint() { return this->currentPoint; };
    int getSteps() { return this->steps; };
    void printCurrentPoint();
    std::string getCurrentPointAsString();
protected:
    int currentPoint[2] = {0, 0};
    int steps = 0;
};

#endif // WALKER_H
