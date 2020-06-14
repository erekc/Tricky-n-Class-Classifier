#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "chartview.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![4]
    ChartView *chartView = new ChartView();
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    ChartView *chartView2 = new ChartView();
    QMainWindow window2;
    window2.setCentralWidget(chartView2);
    window2.resize(700, 400);
    window2.show();
//![4]

    return a.exec();
}
