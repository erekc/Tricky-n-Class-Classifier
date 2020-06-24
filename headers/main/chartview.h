#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMargins>
#include <QRectF>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QColor>
#include <vector>
#include <memory>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0) : QChartView(new QChart(), parent), r(30), g(20), b(10) {}
    void addSeriesToList(std::string seriesName, xt::xarray<double>& dataPoints);
    void plotChart();
    void showChart();
private:
    std::vector<std::unique_ptr<QScatterSeries>> seriesList;
    QMainWindow window;
    int r;
    int g;
    int b;
};

#endif // CHARTVIEW_H

