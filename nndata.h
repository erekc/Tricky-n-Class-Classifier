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
    NNData();
    NNData(int numSamples, int dimension) : numSamples(numSamples), dimension(dimension), chartView(std::make_unique<ChartView>()){}
    xt::xarray<double> getData(){ return this->data; }
    virtual void generateData();
    void showData();
protected:
    xt::xarray<double> data;
    int numSamples;
    int dimension;
    std::unique_ptr<ChartView> chartView;
};

#endif // NNDATA_H
