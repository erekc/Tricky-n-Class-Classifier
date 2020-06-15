#ifndef NNDATA_H
#define NNDATA_H

#include <string>
#include <iostream>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "xtensor/xrandom.hpp"

class NNData
{
public:
    NNData();
    NNData(int numSamples, int dimension) : numSamples(numSamples), dimension(dimension){}
    xt::xarray<double> getData(){ return this->data; }
    virtual void generateData();
protected:
    xt::xarray<double> data;
    int numSamples;
    int dimension;
};

#endif // NNDATA_H
