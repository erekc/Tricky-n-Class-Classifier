#include "../../headers/test/nndatatest.h"
#include "../../headers/test/nntrainingdatatest.h"

void acceptNNTrainingDataByValue(NNTrainingDataTest data){
    std::cout << "Accepted NNTrainingData by value" << std::endl;
    // data destructs
}

void test1(){
    NNTrainingDataTest data1 = NNTrainingDataTest(50, 2, 3); // Constructor
    NNTrainingDataTest data2 = NNTrainingDataTest(100, 2, 3); // Constructor
    data1 = data2; // Copy Assignment
    NNTrainingDataTest data3(data1); // Copy Constructor
    NNTrainingDataTest data4(std::move(data2)); //Move Constructor
    data4 = std::move(data3); // Move Assignment
    // Everything destructs (4 objects total)
}

void test2(){
    NNTrainingDataTest data1 = NNTrainingDataTest(50, 2, 3); // Constructor
    NNTrainingDataTest data2 = NNTrainingDataTest(100, 2, 3); // Constructor
    NNTrainingDataTest data3(data1); // Copy Constructor
    {
        NNTrainingDataTest data4(std::move(data2)); // Move Constructor (invalidates data2)
        {
            NNTrainingDataTest data5 = NNTrainingDataTest(75, 2, 3);
            data5 = data4; // Copy Assignment
            data5 = std::move(data3); // Move Assignment (invalidates data3)
            // data5 destructs
        }
        // data4 destructs
    }
    acceptNNTrainingDataByValue(data1); // Copy constructor and Destructor called inside function
    // data1, data2, and data3 destructs
}

int main(){
    test1();
    test2();
    return 0;
}
