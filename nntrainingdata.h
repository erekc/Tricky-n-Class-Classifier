#ifndef NNTRAININGDATA_H
#define NNTRAININGDATA_H

#include "nndata.h"
#include <cstdlib>
#include <memory>
#include <random>
#include <string>
#include "xtensor/xadapt.hpp"
#include "xtensor/xbuilder.hpp"
#include "xtensor/xview.hpp"

class NNTrainingData : public NNData {
public:
    NNTrainingData();
    NNTrainingData(int numSamples, int dimension, int numClasses) : NNData(numSamples, dimension), numClasses(numClasses){}
    void generateData() override;
    std::vector<int> getLabels() { return this->labels; }
private:
    void addClassDataToChart();
    std::vector<int> labels;
    int numClasses;
};

#endif // NNTRAININGDATA_H
