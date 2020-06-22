#include "chartview.h"
#include "nndata.h"
#include "nntrainingdata.h"
#include "walker.h"
#include "spiralwalker.h"

QT_CHARTS_USE_NAMESPACE

void test(){
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
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int dataSelection;
    int loadIndication;
    std::string pathToLoad;
    int saveIndicator;
    std::string pathToSave;

    std::cout << "Hello there. This is a program that generates data for which is intended use ";
    std::cout << "is for testing or training a simplet Tricky n Class Classifying Neural Network. ";
    std::cout << "An awesome feature about the data generation is that when the Network is trained ";
    std::cout << "on and tested using the data, you'll get an awesome regional data plot! ";
    std::cout << "This utility also doubles as a visualization tool so that you can plot your data ";
    std::cout << "to see what it looks like. One important note: because this program is also built ";
    std::cout << "for displaying data, it will only work for data of dimension 2. Let's begin!" << std::endl << std::endl;

    std::cout << "What kind of data would you like? " << std::endl;
    std::cout << "Please select either Test (0) or Training (1)." << std::endl;
    std::cin >> dataSelection;
    while (dataSelection != 0 && dataSelection != 1){
        std::cout << "Your selection is invalid. Please select either Test (0) or Training (1)." << std::endl;
        std::cin >> dataSelection;
    }
    if (dataSelection == 0){
        std::cout << "You have selected Test data." << std::endl;
    }
    else {
        std::cout << "You have selected Training data." << std::endl;
    }

    std::cout << "Would you like to generate data (0) or load existing data (1)?" << std::endl;
    std::cin >> loadIndication;
    while (loadIndication != 0 && loadIndication != 1){
        std::cout << "Your selection is invalid. Please select generate (0) or load (1)." << std::endl;
        std::cin >> loadIndication;
    }

    if (loadIndication == 1){
        std::cout << "You have chosen to load data. Please provide the path of the file to be loaded." << std::endl;
        std::cin >> pathToLoad;
        std::ifstream inputFile;
        inputFile.open(pathToLoad);
        while (!inputFile.is_open()){
            std::cout << "The specified file could not be opened. Please input valid path." << std::endl;
            std::cin >> pathToLoad;
            inputFile.open(pathToLoad);
        }
        inputFile.close();
    }
    if (loadIndication == 0){
        std::cout << "You have chosen not to load data. ";
        std::cout << "Would you like the generated data to be saved to a file? ";
        std::cout << "(no (0) or yes (1))" << std::endl;
        std::cin >> saveIndicator;
        while (saveIndicator != 0 && saveIndicator != 1){
            std::cout << "Your response is invalid. Please select no (0) or yes (1)." << std::endl;
            std::cin >> saveIndicator;
        }
        if (saveIndicator == 1){
            std::cout << "Please specify the path to the file to which you would like the data to be saved." << std::endl;
            std::cin >> pathToSave;
            std::ofstream outputFile;
            outputFile.open(pathToSave);
            while (!outputFile.is_open()){
                std::cout << "The specified file could not be opened. Please input valid path." << std::endl;
                std::cin >> pathToSave;
                outputFile.open(pathToSave);
            }
            outputFile.close();
        }

    }

    int numSamples;
    int dimension = 2;
    if (dataSelection == 0){
        std::cout << "How many samples would you like for your test data?" << std::endl;
        std::cin >> numSamples;
        NNData data = NNData(numSamples, dimension);
        if (loadIndication == 1){
            data.loadFromFile(pathToLoad);
        }
        else {
            data.generateData();
            if (saveIndicator == 1){
                data.writeToFile(pathToSave);
            }
        }
        data.showData();
        return a.exec();
    }
    else {
        int numClasses;
        std::cout << "How many classes would you like?" << std::endl;
        std::cin >> numClasses;
        std::cout << "How many samples would you like for each class for your training data?" << std::endl;
        std::cin >> numSamples;
        NNTrainingData trainingData = NNTrainingData(numSamples, dimension, numClasses);
        if (loadIndication == 1){
            trainingData.loadFromFile(pathToLoad);
        }
        else {
            trainingData.generateSpiralingData(numClasses, numSamples);
            if (saveIndicator == 1){
                trainingData.writeToFile(pathToSave);
            }
        }
        trainingData.showData();
        return a.exec();
    }
}
