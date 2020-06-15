#include "chartview.h"
#include "nndata.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NNData nndata = NNData(100, 2);
    nndata.generateData();
    xt::xarray<double> data = nndata.getData();

    std::unique_ptr<ChartView> chartView = std::make_unique<ChartView>();
    chartView->addSeriesToList("nndata", data);

    chartView->plotChart();

    chartView->showChart();

    return a.exec();
}
