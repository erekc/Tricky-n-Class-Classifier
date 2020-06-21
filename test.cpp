#include "chartview.h"
#include "nndata.h"
#include "nntrainingdata.h"
#include "spiralwalker.h"
#include "walker.h"


void acceptNNTrainingDataByValue(NNTrainingData data){
    std::cout << "Accepted NNTrainingData by value" << std::endl;
}

int main(){
    NNTrainingData data1 = NNTrainingData(50, 2, 3); // Constructor
    NNTrainingData data2 = NNTrainingData(100, 2, 3); // Constructor
    NNTrainingData data3(data1); // Copy Constructor
    {
        NNTrainingData data4(std::move(data2)); // Move Constructor (invalidates data2)
        {
            NNTrainingData data5 = NNTrainingData(75, 2, 3);
            data5 = data4; // Copy Assignment
            data5 = std::move(data3); // Move Assignment (invalidates data3)
            // data5 destructs
        }
        // data4 destructs
    }
    acceptNNTrainingDataByValue(data1); // Copy constructor and Destructor called inside function
    // data1, data2, and data3 destructs
    return 0;
}
