#ifndef NNDATATEST_H
#define NNDATATEST_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "xtensor/xrandom.hpp"

class NNDataTest
{
public:
    NNDataTest(int numSamples, int dimension);
    virtual ~NNDataTest();
    NNDataTest(const NNDataTest& source);
    NNDataTest& operator=(const NNDataTest& source);
    NNDataTest(NNDataTest&& source);
    NNDataTest& operator=(NNDataTest&& source);
    xt::xarray<double> getData(){ return *(this->data); }
    virtual void generateData();
    virtual void writeToFile(std::string filename);
    virtual void loadFromFile(std::string filename);
protected:
    xt::xarray<double>* data;
    int numSamples;
    int dimension;
};

#endif // NNDATATEST_H
