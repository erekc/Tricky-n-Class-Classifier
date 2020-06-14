#include "chartview.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    xt::xarray<double> arr1 =
    {{0, 2},
     {1, 2},
     {2, 2},
     {3, 2},
     {4, 2}};

    xt::xarray<double> arr2 =
    {{0, 4},
     {1, 4},
     {2, 4},
     {3, 4},
     {4, 4}};

    xt::xarray<double> arr3 =
    {{0, 6},
     {1, 6},
     {2, 6},
     {3, 6},
     {4, 6}};

    std::unique_ptr<ChartView> chartView = std::make_unique<ChartView>();

    chartView->addSeriesToList("series1", arr1);
    chartView->addSeriesToList("series2", arr2);
    chartView->addSeriesToList("series3", arr3);

    chartView->plotChart();

    chartView->showChart();

    return a.exec();
}
