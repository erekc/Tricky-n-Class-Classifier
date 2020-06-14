#include "chartview.h"

void ChartView::addSeries(std::string seriesName, xt::xarray<double> dataPoints){
    std::unique_ptr<QScatterSeries> series = std::make_unique<QScatterSeries>();
    series->setName(seriesName.data());
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series->setMarkerSize(10.0);

    int numPoints = static_cast<int>(dataPoints.shape(0));
    for (int i = 0; i < numPoints; ++i){
        auto dataPoint = xt::view(dataPoints, i, xt::all());
        *series << QPointF(dataPoint(0), dataPoint(1));
    }

    this->seriesList.emplace_back(std::move(series));
}

void ChartView::plotChart(){
    this->setRenderHint(QPainter::Antialiasing);

    for (auto& series: this->seriesList){
        this->chart()->addSeries(series.get());
    }

    this->chart()->setTitle("Simple scatterchart example");
    this->chart()->createDefaultAxes();
    this->chart()->setDropShadowEnabled(false);
    this->chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
}

void ChartView::showChart(){
    this->plotChart();
    this->window.setCentralWidget(this);
    this->window.resize(400, 300);
    this->window.show();
}
