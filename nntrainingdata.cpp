#include "nntrainingdata.h"

void NNTrainingData::generateData(){
    std::vector<std::size_t> shape = {1, static_cast<size_t>(this->dimension)};
    for (int i = 0; i < this->numSamples; ++i){
        std::unique_ptr<double[]> featureVector(new double[this->dimension]);
        double sum = 0;
        for (int j = 0; j < this->dimension; ++j){
            featureVector[j] = rand() % 2;
            sum += featureVector[j];
        }
    }


}
