#include "nndatatest.h"

NNDataTest::NNDataTest(int numSamples, int dimension) :
    numSamples(numSamples), dimension(dimension){
    std::vector<std::size_t> dataShape = {static_cast<size_t>(this->numSamples), static_cast<size_t>(this->dimension)};
    this->data = new xt::xarray<double, xt::layout_type::row_major>(dataShape);
    std::cout << "NNDataTest Constructor" << std::endl;
}

NNDataTest::~NNDataTest(){
    delete this->data;
    std::cout << "NNDataTest Destructor" << std::endl;
}

NNDataTest::NNDataTest(const NNDataTest& source){
    std::vector<std::size_t> dataShape = {static_cast<size_t>(source.numSamples), static_cast<size_t>(source.dimension)};
    this->data = new xt::xarray<double, xt::layout_type::row_major>(dataShape);
    *(this->data) = *(source.data);
    this->dimension = source.dimension;
    this->numSamples = source.numSamples;
    std::cout << "NNDataTest Copy Constructor" << std::endl;
}

NNDataTest& NNDataTest::operator=(const NNDataTest &source){
    if (this == &source){
        return *this;
    }

    delete this->data;

    std::vector<std::size_t> dataShape = {static_cast<size_t>(source.numSamples), static_cast<size_t>(source.dimension)};
    this->data = new xt::xarray<double, xt::layout_type::row_major>(dataShape);
    *(this->data) = *(source.data);
    this->dimension = source.dimension;
    this->numSamples = source.numSamples;
    std::cout << "NNDataTest Copy Assignment" << std::endl;

    return *this;
}

NNDataTest::NNDataTest(NNDataTest&& source){
    this->data = source.data;
    this->dimension = source.dimension;
    this->numSamples = source.numSamples;
    source.data = nullptr;
    source.dimension = 0;
    source.numSamples = 0;
    std::cout << "NNDataTest Move Constructor" << std::endl;
}

NNDataTest& NNDataTest::operator=(NNDataTest&& source){
    if (this == &source){
        return *this;
    }

    delete this->data;

    this->data = source.data;
    this->dimension = source.dimension;
    this->numSamples = source.numSamples;
    source.data = nullptr;
    source.dimension = 0;
    source.numSamples = 0;
    std::cout << "NNData Move Assignment" << std::endl;

    return *this;
}

void NNDataTest::generateData(){
    *(this->data) = std::move(xt::random::randn<double>({this->numSamples, this->dimension}));
}

void NNDataTest::writeToFile(std::string filename){
    std::ofstream outputFile;
    outputFile.open(filename);
    if (outputFile.is_open()){
        outputFile << this->numSamples << " " << this->dimension << std::endl;
        for (int i = 0; i < this->numSamples; ++i){
            auto row = xt::row(*(this->data), i);
            for (int j = 0; j < this->dimension; ++j){
                outputFile << row(0, j) << " ";
            }
            outputFile << std::endl;
        }
        outputFile.close();
    }
    else{
        std::cout << "File could not be opened for writing. No data written." << std::endl;
    }
}

void NNDataTest::loadFromFile(std::string filename){
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

        int row = 0;
        while(std::getline(inputFile, line)){
            std::istringstream rowstream(line);
            rowstream >> (*(this->data))(row, 0);
            rowstream >> (*(this->data))(row, 1);
            row++;
        }

        inputFile.close();
    }
    else{
        std::cout << "File could not be opened for reading. No data read." << std::endl;
    }
}
