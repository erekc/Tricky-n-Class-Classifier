#include "chartview.h"

void ChartView::plot()
{
    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(10.0);

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter2");
    series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series1->setMarkerSize(10.0);

    QScatterSeries *series2 = new QScatterSeries();
    series2->setName("scatter3");
    series2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series2->setMarkerSize(10.0);

    series0->append(0, 6);
    series0->append(2, 4);
    series0->append(3, 8);
    series0->append(7, 4);
    series0->append(10, 5);

    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);
    *series2 << QPointF(1, 5) << QPointF(4, 6) << QPointF(6, 3) << QPointF(9, 5);

    setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series0);
    chart()->addSeries(series1);
    chart()->addSeries(series2);

    chart()->setTitle("Simple scatterchart example");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);

    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
}
