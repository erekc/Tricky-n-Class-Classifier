#ifndef NNDATA_H
#define NNDATA_H

#include "chartview.h"
#include <string>
#include <iostream>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "xtensor/xrandom.hpp"

class NNData
{
public:
    NNData(int numSamples, int dimension);
    ~NNData();
    NNData(const NNData& source);
    NNData& operator=(const NNData& source);
    NNData(NNData&& source);
    NNData& operator=(NNData&& source);
    xt::xarray<double> getData(){ return *(this->data); }
    virtual void generateData();
    void showData();
protected:
    xt::xarray<double>* data;
    int numSamples;
    int dimension;
    std::shared_ptr<ChartView> chartView;
};

#endif // NNDATA_H
