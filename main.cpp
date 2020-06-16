#include "chartview.h"
#include "nndata.h"
#include "nntrainingdata.h"
#include "walker.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    NNData nndata = NNData(100, 2);
//    nndata.generateData();
//    nndata.showData();

//    NNTrainingData trainingData = NNTrainingData(100, 2, 3);
//    trainingData.generateData();
//    trainingData.showData();

    Walker walker = Walker();
    walker.walk();
    walker.printCurrentPoint();

    return a.exec();
}
