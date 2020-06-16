#include "walker.h"

Walker::Walker(){}

void Walker::reset(){
    this->currentPoint[0] = 0;
    this->currentPoint[1] = 0;
    this->steps = 0;
}

void Walker::walk(){
    this->currentPoint[0]++;
    this->currentPoint[1]++;
    this->steps++;
}

void Walker::printCurrentPoint(){
    std::cout << "CurrentPoint: ";
    std::cout << "{ " << this->currentPoint[0] << ", " << this->currentPoint[1] << " }";
    std::cout << std::endl;
}
