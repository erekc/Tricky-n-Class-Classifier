#include "chartview.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    xt::xarray<double> arr1 =
    {{0, 6},
     {2, 4},
     {3, 8},
     {7, 4},
     {10, 5}};

    xt::xarray<double> arr2 =
    {{1, 1},
     {3, 3},
     {7, 6},
     {8, 3},
     {10, 2}};

    xt::xarray<double> arr3 =
    {{1, 5},
     {4, 6},
     {6, 3},
     {9, 5}};

    ChartView *chartView = new ChartView();

    chartView->addSeries("series1", arr1);
    chartView->addSeries("series2", arr2);
    chartView->addSeries("series3", arr3);

    chartView->plotChart();

    chartView->showChart();

    return a.exec();
}
