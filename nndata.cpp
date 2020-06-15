#include "nndata.h"

void NNData::generateData(){
    this->data = xt::random::randn<double>({this->numSamples, this->dimension});
}
