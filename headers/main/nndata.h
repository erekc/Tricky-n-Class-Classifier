#ifndef NNDATA_H
#define NNDATA_H

#include "chartview.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "xtensor/xrandom.hpp"

class NNData
{
public:
    NNData(int numSamples, int dimension);
    virtual ~NNData();
    NNData(const NNData& source);
    NNData& operator=(const NNData& source);
    NNData(NNData&& source);
    NNData& operator=(NNData&& source);
    virtual void generateData();
    virtual void writeToFile(std::string filename);
    virtual void loadFromFile(std::string filename);
    void showData();
    xt::xarray<double> getData(){ return *(this->data); }
    int getNumSamples(){ return this->numSamples; };
    int getDimension(){ return this->dimension; };

protected:
    xt::xarray<double>* data;
    int numSamples;
    int dimension;
    std::shared_ptr<ChartView> chartView;
};

#endif // NNDATA_H
