#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include <vector>
#include <memory>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0);
private:
    std::vector<std::unique_ptr<QScatterSeries>> series;
};

#endif // CHARTVIEW_H

