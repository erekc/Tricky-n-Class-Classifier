#include "nndata.h"

NNData::NNData(int numSamples, int dimension) :
    numSamples(numSamples), dimension(dimension), chartView(std::make_shared<ChartView>()){
    std::vector<std::size_t> dataShape = {static_cast<size_t>(this->numSamples), static_cast<size_t>(this->dimension)};
    this->data = new xt::xarray<double, xt::layout_type::row_major>(dataShape);
    std::cout << "NNData Constructor" << std::endl;
}

NNData::~NNData(){
    delete this->data;
    std::cout << "NNData Destructor" << std::endl;
}

NNData::NNData(const NNData& source){
    std::vector<std::size_t> dataShape = {static_cast<size_t>(source.numSamples), static_cast<size_t>(source.dimension)};
    this->data = new xt::xarray<double, xt::layout_type::row_major>(dataShape);
    *(this->data) = *(source.data);
    this->dimension = source.dimension;
    this->numSamples = source.numSamples;
    this->chartView = source.chartView;
    std::cout << "NNData Copy Constructor" << std::endl;
}

NNData& NNData::operator=(const NNData &source){
    if (this == &source){
        return *this;
    }

    delete this->data;

    std::vector<std::size_t> dataShape = {static_cast<size_t>(source.numSamples), static_cast<size_t>(source.dimension)};
    this->data = new xt::xarray<double, xt::layout_type::row_major>(dataShape);
    *(this->data) = *(source.data);
    this->dimension = source.dimension;
    this->numSamples = source.numSamples;
    this->chartView = source.chartView;
    std::cout << "NNData Copy Assignment" << std::endl;

    return *this;
}

NNData::NNData(NNData&& source){
    this->data = source.data;
    this->dimension = source.dimension;
    this->numSamples = source.numSamples;
    this->chartView = source.chartView;
    source.data = nullptr;
    source.dimension = 0;
    source.numSamples = 0;
    std::cout << "NNData Move Constructor" << std::endl;
}

NNData& NNData::operator=(NNData&& source){
    if (this == &source){
        return *this;
    }

    delete this->data;

    this->data = source.data;
    this->dimension = source.dimension;
    this->numSamples = source.numSamples;
    this->chartView = source.chartView;
    source.data = nullptr;
    source.dimension = 0;
    source.numSamples = 0;
    std::cout << "NNData Move Assignment" << std::endl;

    return *this;
}

void NNData::generateData(){
    *(this->data) = std::move(xt::random::randn<double>({this->numSamples, this->dimension}));
    this->chartView->addSeriesToList("nndata", *(this->data));
    this->chartView->setRubberBand(QChartView::RectangleRubberBand);
}

void NNData::showData(){
    this->chartView->showChart();
}

void NNData::writeToFile(std::string filename){
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

void NNData::loadFromFile(std::string filename){
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
