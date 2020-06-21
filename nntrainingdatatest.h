#ifndef NNTRAININGDATATEST_H
#define NNTRAININGDATATEST_H

#include "nndatatest.h"
#include "spiralwalker.h"
#include <cstdlib>
#include <memory>
#include <random>
#include <string>
#include "xtensor/xadapt.hpp"
#include "xtensor/xbuilder.hpp"
#include "xtensor/xview.hpp"

class NNTrainingDataTest : public NNDataTest {
public:
    NNTrainingDataTest(int numSamples, int dimension, int numClasses);
    ~NNTrainingDataTest();
    NNTrainingDataTest(const NNTrainingDataTest& source);
    NNTrainingDataTest& operator=(const NNTrainingDataTest& source);
    NNTrainingDataTest(NNTrainingDataTest&& source);
    NNTrainingDataTest& operator=(NNTrainingDataTest&& source);
    void generateData() override;
    void generateSpiralingData(int classes, int dataPoints);
    int* getLabels() { return this->labels; }
    void writeToFile(std::string filename) override;
    void loadFromFile(std::string filename) override;
private:
    int* labels;
    int numClasses;
};

#endif // NNTRAININGDATATEST_H
