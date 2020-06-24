#include "../../headers/common/spiralwalker.h"

void SpiralWalker::reset(){
    this->currentPoint[0] = 0;
    this->currentPoint[1] = 0;
    this->steps = 0;
    this->startingPoint[0] = 0;
    this->startingPoint[1] = 0;
    this->reach = 0;
    this->corners = 0;
    this->whichIncrement = 0;
}

void SpiralWalker::walk(){
    if (this->isStart()){
        this->reach++;
        this->corners = 0;
        this->whichIncrement = 0;
        this->startingPoint[0] = this->reach;
        this->startingPoint[1] = this->reach;
        this->currentPoint[0] = this->reach - 1;
        this->currentPoint[1] = this->reach;
    }
    else {
        if (this->endOfSide()){
            this->corners++;
            this->whichIncrement = static_cast<int>(!this->whichIncrement);
        }
        this->currentPoint[this->whichIncrement] += 1 - (2 * static_cast<int>(this->corners < 2));
    }
    this->steps++;
}

bool SpiralWalker::isStart(){
    return (this->startingPoint[0] == this->currentPoint[0]) && (this->startingPoint[1] == this->currentPoint[1]);
}

bool SpiralWalker::endOfSide(){
    return abs(this->currentPoint[this->whichIncrement]) == this->reach;
}
