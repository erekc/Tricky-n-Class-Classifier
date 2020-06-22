#ifndef NNTRAININGDATA_H
#define NNTRAININGDATA_H

#include "nndata.h"
#include "spiralwalker.h"
#include <cstdlib>
#include <memory>
#include <random>
#include <string>
#include "xtensor/xadapt.hpp"
#include "xtensor/xbuilder.hpp"
#include "xtensor/xview.hpp"

class NNTrainingData : public NNData {
public:
    NNTrainingData(int numSamples, int dimension, int numClasses);
    ~NNTrainingData();
    NNTrainingData(const NNTrainingData& source);
    NNTrainingData& operator=(const NNTrainingData& source);
    NNTrainingData(NNTrainingData&& source);
    NNTrainingData& operator=(NNTrainingData&& source);
    void generateData() override;
    void generateSpiralingData(int classes, int dataPoints);
    void writeToFile(std::string filename) override;
    void loadFromFile(std::string filename) override;
    int* getLabels() { return this->labels; }
    int getNumClasses(){ return this->numClasses; };

private:
    void addClassDataToChart();
    int* labels;
    int numClasses;
};

#endif // NNTRAININGDATA_H
