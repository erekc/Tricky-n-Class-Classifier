#include "chartview.h"
#include "nndata.h"
#include "nntrainingdata.h"
#include "walker.h"
#include "spiralwalker.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    {
//        std::cout << "NNData Rule of Five Test" << std::endl;
//        NNData nndata = NNData(100, 2);
//        NNData nndata2 = NNData(100, 2);
//        nndata2 = nndata;
//        NNData nndata3(nndata);
//        NNData nndata4(std::move(nndata2));
//        nndata4 = std::move(nndata);
//        std::cout << "NNTrainingData Rule of Five Test" << std::endl;
//        NNTrainingData nntrainingdata = NNTrainingData(50, 2, 3);
//        NNTrainingData nntrainingdata2 = NNTrainingData(50, 2, 3);
//        nntrainingdata = nntrainingdata2;
//        NNTrainingData nntrainingdata3(nntrainingdata);
//        NNTrainingData nntrainingdata4(std::move(nntrainingdata2));
//        nntrainingdata4 = std::move(nntrainingdata);
//        std::cout << "End of Rule of Five Test Scope" << std::endl;
//    }
    std::cout << "App Test" << std::endl;
    std::cout << "NNData Test" << std::endl;
    NNData nndata = NNData(100, 2);
    nndata.generateData();
    nndata.showData();
    std::cout << nndata.getData() << std::endl << std::endl << std::endl;
    nndata.writeToFile("nndata.txt");
    nndata.loadFromFile("nndata.txt");
    std::cout << nndata.getData() << std::endl;

    std::cout << "NNTrainingData Test" << std::endl;
    NNTrainingData trainingData = NNTrainingData(100, 2, 3);
    trainingData.generateSpiralingData(3, 50);
    std::cout << trainingData.getData() << std::endl << std::endl << std::endl;
    trainingData.writeToFile("nntrainingdata.txt");
    trainingData.loadFromFile("nntrainingdata.txt");
    std::cout << trainingData.getData() << std::endl;
    trainingData.showData();

    std::cout << "Walker Tests" << std::endl;
    Walker walker = Walker();
    walker.walk();
    walker.printCurrentPoint();

    SpiralWalker spiralWalker = SpiralWalker();
    for (int i = 0; i < 14; i++){
        std::cout << spiralWalker.getCurrentPointAsString() << " Step: " << spiralWalker.getSteps() << std::endl;
        spiralWalker.walk();
    }
    return a.exec();
}
