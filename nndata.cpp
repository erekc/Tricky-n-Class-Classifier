#include "nndata.h"

void NNData::generateData(){
    this->data = std::move(xt::random::randn<double>({this->numSamples, this->dimension}));
    this->chartView->addSeriesToList("nndata", this->data);
    this->chartView->setRubberBand(QChartView::RectangleRubberBand);
}

void NNData::showData(){
    this->chartView->plotChart();
    this->chartView->showChart();
}
