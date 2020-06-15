#ifndef NNTRAININGDATA_H
#define NNTRAININGDATA_H

#include "nndata.h"
#include <cstdlib>
#include <memory>

class NNTrainingData : public NNData {
public:
    NNTrainingData();
    NNTrainingData(int numSamples, int dimension) : NNData(numSamples, dimension) {}
    void generateData() override;
    xt::xarray<double> getLabels() { return this->labels; }
private:
    xt::xarray<double> labels;
};

#endif // NNTRAININGDATA_H
