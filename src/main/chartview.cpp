#include "../../headers/main/chartview.h"

void ChartView::addSeriesToList(std::string seriesName, xt::xarray<double>& dataPoints){
    std::unique_ptr<QScatterSeries> series = std::make_unique<QScatterSeries>();
    series->setName(seriesName.data());
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series->setMarkerSize(10.0);
    QColor color = QColor(this->r, this->g, this->b);
    series->setColor(color);
    this->r = static_cast<int>(2.0 * this->r) % 255;
    this->g = static_cast<int>(1.625 * this->g) % 255;
    this->b = static_cast<int>(1.25 * this->b) % 255;

    int numPoints = static_cast<int>(dataPoints.shape(0));
    for (int i = 0; i < numPoints; ++i){
        auto dataPoint = xt::view(dataPoints, i, xt::all());
        *series << QPointF(dataPoint(0), dataPoint(1));
    }

    this->seriesList.emplace_back(std::move(series));
}

void ChartView::plotChart(){
    this->setRenderHint(QPainter::Antialiasing);
    
    std::vector<std::unique_ptr<QScatterSeries>>::iterator it;
    for (it = this->seriesList.begin(); it != this->seriesList.end(); it++){
        this->chart()->addSeries((*it).get());
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
