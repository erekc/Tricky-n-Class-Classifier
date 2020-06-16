#ifndef SPIRALWALKER_H
#define SPIRALWALKER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "walker.h"

class SpiralWalker : public Walker
{
public:
    void walk() override;
    void reset() override;
private:
    bool isStart();
    bool endOfSide();
    int reach = 0;
    int startingPoint[2] = {0,0};
    int whichIncrement = 0;
    int corners = 0;
};

#endif // SPIRALWALKER_H
