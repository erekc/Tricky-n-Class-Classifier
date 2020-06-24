#include "../../headers/test/nntrainingdatatest.h"
#include <typeinfo>
#include <iostream>


NNTrainingDataTest::NNTrainingDataTest(int numSamples, int dimension, int numClasses) :
    NNDataTest(numSamples, dimension), labels(new int[numSamples]), numClasses(numClasses) {
    std::cout << "NNTrainingDataTest Constructor" << std::endl;
}

NNTrainingDataTest::~NNTrainingDataTest(){
    delete[] this->labels;
    std::cout << "NNTrainingDataTest Destructor" << std::endl;
}

NNTrainingDataTest::NNTrainingDataTest(const NNTrainingDataTest& source) : NNDataTest(source){
    this->numClasses = source.numClasses;
    this->labels = new int[source.numSamples];
    std::memcpy(this->labels, source.labels, sizeof(int) * this->numSamples);
    std::cout << "NNTrainingDataTest Copy Constructor" << std::endl;
}

NNTrainingDataTest& NNTrainingDataTest::operator=(const NNTrainingDataTest& source){
    if (this == &source){
        return *this;
    }
    NNDataTest::operator=(source);
    delete[] this->labels;
    this->labels = new int[source.numSamples];
    std::memcpy(this->labels, source.labels, sizeof(int) * this->numSamples);
    this->numClasses = source.numClasses;
    std::cout << "NNTrainingDataTest Copy Assignment" << std::endl;
    return *this;
}

NNTrainingDataTest::NNTrainingDataTest(NNTrainingDataTest&& source) : NNDataTest(std::move(source)){
    this->numClasses = source.numClasses;
    this->labels = source.labels;
    source.labels = nullptr;
    source.numClasses = 0;
    std::cout << "NNTrainingDataTest Move Constructor" << std::endl;
}

NNTrainingDataTest& NNTrainingDataTest::operator=(NNTrainingDataTest&& source){
    if (this == &source){
        return *this;
    }
    NNDataTest::operator=(std::move(source));
    delete[] this->labels;
    this->labels = source.labels;
    this->numClasses = source.numClasses;
    source.labels = nullptr;
    source.numClasses = 0;
    std::cout << "NNTrainingDataTest Move Assignment" << std::endl;
    return *this;
}

void NNTrainingDataTest::generateData(){

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    delete[] this->labels;
    this->labels = new int[this->numSamples];

    for (int i = 0; i < this->numSamples; ++i){
        int sum = 0;
        for (int j = 0; j < this->dimension; ++j){
            int x = rand() % 2;
            sum += x;
            (*(this->data))(i, j) = 1.0 * x + 0.20 * distribution(generator);
        }
        this->labels[i] = sum;
    }
}

void NNTrainingDataTest::generateSpiralingData(int classes, int dataPoints){

    this->numClasses = classes;
    this->numSamples = dataPoints * classes;
    this->dimension = 2;

    delete[] this->labels;
    this->labels = new int[this->numSamples];

    delete this->data;
    std::vector<std::size_t> dataShape = {static_cast<size_t>(this->numSamples), 2};
    this->data = new xt::xarray<double, xt::layout_type::row_major>(dataShape);

    SpiralWalker spiralWalker = SpiralWalker();

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < this->numClasses; ++i){

        int* currentPoint = spiralWalker.getCurrentPoint();
        int row = *(currentPoint + 0);
        int col = *(currentPoint + 1);
        for (int j = i * dataPoints ; j < (i + 1) * dataPoints; ++j){
            double newRow = 1.0 * row + 0.2 * distribution(generator);
            double newCol = 1.0 * col + 0.2 * distribution(generator);
            (*(this->data))(j, 0) = newRow;
            (*(this->data))(j, 1) = newCol;
            this->labels[j] = i;
        }
        spiralWalker.walk();
    }
}

void NNTrainingDataTest::writeToFile(std::string filename){
    std::ofstream outputFile;
    outputFile.open(filename);
    if (outputFile.is_open()){
        outputFile << this->numSamples << " " << this->dimension << std::endl;
        for (int i = 0; i < this->numSamples; ++i){
            auto row = xt::row(*(this->data), i);
            for (int j = 0; j < this->dimension; ++j){
                outputFile << row(0, j) << " ";
            }
            outputFile << this->labels[i] << std::endl;
        }
        outputFile.close();
    }
    else{
        std::cout << "File could not be opened for writing. No data written." << std::endl;
    }
}

void NNTrainingDataTest::loadFromFile(std::string filename){
    std::string line;
    std::ifstream inputFile;
    inputFile.open(filename);
    if (inputFile.is_open()){

        std::getline(inputFile, line);
        std::istringstream ss(line);
        ss >> this->numSamples;
        ss >> this->dimension;

        delete this->data;
        std::vector<std::size_t> dataShape = {static_cast<size_t>(this->numSamples), static_cast<size_t>(this->dimension)};
        this->data = new xt::xarray<double, xt::layout_type::row_major>(dataShape);
        delete[] this->labels;
        this->labels = new int[this->numSamples];

        int row = 0;
        while(std::getline(inputFile, line)){
            std::istringstream rowstream(line);
            rowstream >> (*(this->data))(row, 0);
            rowstream >> (*(this->data))(row, 1);
            rowstream >> this->labels[row];
            row++;
        }

        inputFile.close();
    }
    else{
        std::cout << "File could not be opened for reading. No data read." << std::endl;
    }
}
