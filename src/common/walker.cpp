#include "../../headers/common/walker.h"

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

std::string Walker::getCurrentPointAsString(){
    std::string i = "{ " + std::to_string(this->currentPoint[0]);
    std::string j = std::to_string(this->currentPoint[1]) + " }";
    std::string point = i + ", " + j;
    return point;
}
