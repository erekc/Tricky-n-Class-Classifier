#include "nntrainingdata.h"
#include <typeinfo>

void NNTrainingData::generateData(){
    std::vector<std::size_t> dataShape = {static_cast<size_t>(this->numSamples), static_cast<size_t>(this->dimension)};
    this->data = xt::xarray<double, xt::layout_type::row_major>(dataShape);

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < this->numSamples; ++i){
        int sum = 0;
        for (int j = 0; j < this->dimension; ++j){
            int x = rand() % 2;
            sum += x;
            this->data(i, j) = 1.0 * x + 0.20 * distribution(generator);
        }
        this->labels.push_back(sum);
    }

    this->addClassDataToChart();

}

void NNTrainingData::addClassDataToChart(){

    std::vector<std::vector<double>> classIndices;
    for (int i = 0; i < this->numClasses; ++i){
        classIndices.push_back(std::vector<double>());
    }

    for (int i = 0; i < this->numSamples; ++i){
        classIndices[this->labels[i]].push_back(i);
    }

    for (int i = 0; i < this->numClasses; ++i){
        std::vector<double> indices = classIndices[i];

        std::vector<std::size_t> classSeriesShape = {static_cast<size_t>(indices.size()), static_cast<size_t>(this->dimension)};
        xt::xarray<double, xt::layout_type::row_major> classSeries = xt::xarray<double, xt::layout_type::row_major>(classSeriesShape);

        int sum = 0;
        for (size_t j = 0; j < indices.size(); ++j){
            auto row = xt::row(this->data, indices[j]);
            //std::cout << row << std::endl;
            for (int k = 0; k < this->dimension; ++k){
                classSeries(j, k) = row(0, k);
            }
            sum += 1;
        }

        this->chartView->addSeriesToList("class" + std::to_string(i), classSeries);
    }
    this->chartView->setRubberBand(QChartView::RectangleRubberBand);
}
