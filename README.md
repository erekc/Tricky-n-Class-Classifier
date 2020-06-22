# Tricky n Class Classifier Data Generation

### Introduction

In exploring many of the project options, I decided to pursue one that stems from my background in Intelligent Systems, particularly Multilayer Perceptrons. In brainstorming for my project, I decided that I wanted to pursue the construction of a simple 2-dimensional n-Class classifying MLP, which given data points, would predict the class of a 2d input vector. To do this, I first needed a way to generate random data so that the predictions can be graphed in a dense, regional manner. From this requirement came the inception of this project: creating a set of classes that can collectively generate different kinds of data and display the results. This idea was perfect for me, as this gives a great intro to C++ and is an involved way to build something upon which I can not only build more features, such as the MLP itself, but also continue to sharpen and strengthen my C++ skills. This project has been a fun way for me to not only complete my first C++ project, but also give me an introduction into the expansive world of C++.

### Installation, Build, & Run

**The instructions below assume that the project will be build using the Udacity student workspace.**

To be able to display the graphs of the generated data, I needed a GUI that provided the capability of displaying charts. As a result, I chose the **Qt** open source library. In addition, to integrate this project into my next level of this project, I needed a library that enabled the use of matrix-like objects, which I found in the **xtensor** library. 

To download **Qt**, use the following command:
```
wget http://download.qt.io/archive/qt/5.14/5.14.2/qt-opensource-linux-x64-5.14.2.run
```
As can be inferred from this link, the projected uses version 5.14.2. After the *.run* file has been downloaded, make sure that it is executable by using the following command to ensure an executable permission:
```
chmod +x qt-opensource-linux-x64-5.14.2.run
```
After proper permissions have been set, the installation can begin by executing the file with the line below:
```
./qt-opensource-linux-x64-5.14.2.run
```
The installer will then present an installer GUI, which will require an account login. If you do not have an account, you can create one by going to [https://qt.io](https://www.qt.io/) and clicking the silhouette next to the search button in the upper right hand corner of the page. Once you login, follow the instructions in the installer. In the portion that asks what to download, go ahead and select the option to download the whole lot (The library is not too big and if you're like me, you'll definitely get hooked and will try to explore all its amazing features!). Once everything is downloaded, the installer should take you to the finish page.

Next, as described above, the project also uses the **xtensor** library. However, the xtl library must be downloaded and compiled from source before hand. To do this, we will clone the **xtl** repository:
```
git clone https://github.com/xtensor-stack/xtl.git
```
Once, cloned, head into the top level of the directory and create and move into the *build* directory:
```
mkdir build && cd build
```
Then build and install the library using the usual build protocols:
```
cmake ..
make install
```
The process is identical for the **xtensor** library. First, clone **xtensor** repository:
```
git clone https://github.com/xtensor-stack/xtensor.git
```
Then build and install the library as previously described.

To build and run the project, first, clone this repository and head into the top level of the directory. The CMakeLists.txt already incorporates the libraries used in the project. The only change that may be needed is to make sure the path specified in ```CMAKE_PREFIX_PATH``` is ```/opt/Qt5.14.2/5.14.2/gcc_64/lib/cmake/``` or wherever the **Qt** library is installed. Once that is ensured, build and compile the directory with the regular protocols:
```
mkdir build && cd build
cmake ..
make
```
This will create an executable for the program (```./Trick-n-Class-Classifier```) and another for testing the rule of five (```./test```).

### Code & Behavior

#### chartview.h & chartview.cpp

These files together contain the class with which the data will be displayed. This class heavily utilizes the **QT** library. Particularly, it extends the ```QChartView``` class provided by the library. One feature of the ```QChartView``` class is that it stores multiple series of data as ```QScatterSeries``` classes, which can simply be seen as a set of data points. In this project's use case, this can be equated to the set of points pertaining one class. One thing to note in the implementation of this derived class is the established exclusive ownership of the ```QScatterSeries``` objects by the ```QChartView``` class in ```chartview.h```. Additionally, the class has members to plot and show the charts, of which the member function ```void plotChart()``` prepares and ```void showChart()``` shows, the latter of which uses the ```QWindow``` class to display the chart. The ```int r```, ```int g```, and ```int b``` member variables are changed in a way that ensures different classes produces different colors, since by default, the library only comes with 5 possible colors, which would mean that any number of classes above 5 would appear to be duplicates, when they are in fact different.

#### nndata.h & nndata.cpp

These files, along with their derived class which will be discussed shortly, make up the muscle of the project. In particular, the class created by these files serve as the base class for a data structure that creates data using the **xtensor** library, a library that enables data to be stored as matrix-like objects. 

First, ```NNData``` contains the ```xt::xarray<double>* data```, ```int numSamples```, ```int dimension```, and ```std::shared_ptr<ChartView> chartView``` member variables. The first variable mentioned is the ```xtensor``` object used to store the data. The shape of this matrix is ```numSamples``` x ```dimension```, where ```numSamples``` is the number of samples and ```dimension``` is the dimension of the data, which for this project is 2. The ```chartView``` member holds the display mechanism of the data described in the previous section. 

The member functions show some of the functionality of this class, which is generating data, displaying the data, writing data to file, and loading data from a file. When the class is used, the user can decide whether to generate new data or load existing data into the data structure. Then, the user is able to take the data and display for visualization and save to a chosen file if the user so chooses. Of note, the ```void generateData()```, ```void writeToFile()```, and ```void loadFromFile()``` member functions are declared with the ```virtual``` keyword because the requirements for these functions may be different for the derived classes based on the type of data, as will be described in the next section.

One key thing to note in the implementation of this class is the utilization of the Rule of Five. The ```xt::xarray<double>* data``` member is allocated on the heap with ```new``` in the constructor. As such, the resource needs to be properly managed, which means the necessity of the implementation of the destructor. As such, the implementation of the copy constructor, copy assignment, move constructor, and move assignment are required. The declarations for the constructors & destructor can be found in nndata.h for which the definitions are written in nndata.cpp.

#### nntrainingdata.h & nntrainingdata.cpp

This class is a derived class from the ```NNData``` base class. The main extension point is the difference between test data and training data in machine learning. Testing data is simply just a set of data points that come without labels. As such, it is simply a matrix that is the number of samples by the dimension. On the other hand, training data additionally comes with labels. As a result, this class not only stores a matrix for the data itself but an array of labels corresponding to the particular data point in the matrix in the member ```int* labels```. Labels mean that there are different classes, which means the number of classes in the dataset should be known, which is reflected in the member ```int numClasses```. Because of the extra set of points that must be stored compared to the base class, the way the class writes to a file, loads from a file, and generates data changes. To reflect this change, the ```void generateData()```, ```void writeToFile()```, and ```void loadFromFile()``` functions are overridden. 

Another added functionality is the ```void addClassDataToChart()``` member function, which simply adds data to the underlying ```ChartView``` member one class at a time. 

The star of this class is the ```void generateSpiralingData()``` member function. This function uses the ```SpiralWalker``` function to generate data points a region at a time per class in an incremental manner in a spiral path in a cartesian plane. For each additional class, the next point in the path is produced around which ```int dataPoints``` number of data points are produced with a 0.2 times a normal distribution of mean 0 and standard deviation 1. An example of the path of regions created with 25 classes is shown below and can be followed by following 1 to 25:

|    i/j      |      -2     |       -1      |        0      |        1      |      2        |
| :----:      |    :----:   |        :----: |  :----:       |  :----:       |   :----:      |
|    2        |      13     |      12       |        11     |       10      |     25        |
|    1        |      14     |       3       |        2      |       9       |     24        |
|    0        |      15     |       4       |        1      |       8       |     23        |
|   -1        |      16     |       5       |        6      |       7       |     22        |
|   -2        |      17     |      18       |       19      |       20      |     21        |

Each point represents a region corresponding to a class, around which data is generated as previously described.

As with the base class, this derived class also implements the Rule of Five, as the destructor is modified to take care of the heap allocated member ```int* labels```. These implementations are straight forward and similar to that of the base class and can be found in ```nntrainingdata.cpp``` for the definitions and ```nntrainingdata.h``` for the declarations.


#### walker.h & walker.cpp

The premise of this class is producing data points on a cartesion plane in a certain pattern, off of which training data is generated as described in the previous section. This class serves as the base class and comes with two member functions defined with the keyword ```virtual``` and they are ```void walk()``` and ```void reset()```. ```void walk()``` sets the ```int* currentPoint``` member to the next point in the patter, while ```void reset()``` resets the object to its initial states, that is, every member is reset to the beginning. Depending on the type of ```Walker``` object derived, the way the ```Walker``` walks and resets will differ depedning on the pattern implemented and the additional members needed to exercise the pattern. The rest of the member variables and member functions are self explanatory.

#### spiralwalker.h & spiralwalker.cpp

This class is derived from the ```Walker``` base class and is the driving force of the the ```void generateSpiralingData()``` member function of the ```NNTrainingData``` class. This class overrides the ```void walk()``` and ```void reset()``` member functions of the base class. Whereas the ```Walker``` walks by simpling incrementing both elements by 1, ```SpiralWalker``` walks by generating points in the pattern described in **nntrainingdata.h & nntrainingdata.cpp** section. Because this patterrn requires additional member variables, the ```void reset()``` function is updated to reset the additional member variables as well. The private member functions ```bool isStart()``` and ```endOfSide()``` are additional functions used in the walking pattern of ```SpiralWalker```.

#### main.cpp

This file contains the main function which serves as the driver for this application. It uses control flow to obtain necessary parameters, such as whether the user would like to generate data or load existing data, what kind of data to generate, how many samples, or if they user would like to save the generated data. To do this, this flow takes input from the user to obtain the parameters. Once the necessary parameters are gathered, the saved data (if specified) will become available and the data will be displayed. 

#### nndatatest.h & nndatatest.cpp

This implementation is the test version of the ```NNData``` class. Essentially this class strips the original of anything that involves the ```ChartView``` class to use in a test to ensure that the raw implementation without the GUI is intuitive and properly implements the Rule of Five. This means removing the ```std::shared_ptr<ChartView> chartView``` member variable and the ```void showData()``` member function.

#### nntrainingdatatest.h & nntrainingdatatest.cpp

This implementation is the test version of the ```NNTrainingData``` class. This class follows the same theme from which this class is derived, ```NNDataTest``` from the previous section, and strips anything involving ```ChartView```, for which this class is removing the ```void addClassDataToChart()``` private member function.

#### test.cpp

This is the final, but an important, file in the project. The sole purpose of this file is to check whether the Rule of Five is correctly implemented. This means after building the executable stemming from this file, the executable is run with **Valgrind**. **Valgrind** is a tool used to spot memory leaks. When run with the executable, the test runs without memory leaks, which shows that the Rule of Five is implemented correctly. This can be done by running the following line after building the code:

```valgrind --leak-check=yes ./test```

The line produces a message that states all allocated memory were properly freed. This test uses the test versions of the classes to ensure that my direct raw implementations are without fault.

### Rubric Criteria

#### Loops & Functions

- The project demonstrates an understanding of C++ functions and control structures.
    - ```nndata.cpp```
    - ```nntrainingdata.cpp```
    - ```spiralwalker.cpp```
    - ```chartview.cpp```
    - ```main.cpp```
    
- The project reads data from a file and process the data, or the program writes data to a file.
    - ```nndata.cpp``` *line 89*
    - ```nndata.cpp``` *line 108*
    - ```nntrainingdata.cpp``` *line 146*
    - ```nntrainingdata.cpp``` *line 165*
    
- The project accepts user input and processes the input.
    - ```main.cpp``` *line 29 - 107*

#### Object Oriented Programming

- The project uses Object Oriented Programming techniques.
    - ```nndata.cpp```
    - ```nntrainingdata.cpp```
    - ```spiralwalker.cpp```
    - ```chartview.cpp```
    
- Classes use appropriate access specifiers for class members.
    - ```nndata.cpp```
    - ```nntrainingdata.cpp```
    - ```spiralwalker.cpp```
    - ```chartview.cpp```
    
- Class constructors utilize member initialization lists.
    - ```nndata.cpp``` *line 3*
    - ```nntrainingdata.cpp``` *line 6*
    - ```nndatatest.cpp``` *line 3*
    - ```nntrainingdatatest.cpp``` *line 6*
    
- Classes abstract implementation details from their interfaces.
    - ```nndata.h```
    - ```nntrainingdata.h```
    - ```walker.h```
    - ```spiralwalker.h```
    
- Classes encapsulate behavior
    - ```nndata.h```
    - ```nntrainingdata.h```
    - ```walker.h```
    - ```spiralwalker.h```
    - ```chartview.h```
    
- Classes follow an appropriate inheritance hierarchy.
    - ```nndata.h```
    - ```nntrainingdata.h```
    - ```walker.h```
    - ```spiralwalker.h```
    - ```chartView.h```
    
- Derived class functions override virtual base class functions.
    - ```nndata.h``` *line 23-25*
    - ```nntrainingdata.h``` *line 14*
    - ```walker.h``` *line 10-11*
    - ```spiralwalker.h``` *line 12-13*

#### Memory Management

- The project uses destructors appropriately.
    - ```nndata.cpp``` *line 10*
    - ```nntrainingdata.cpp``` *line 11*
    - ```nndatatest.cpp``` *line 10*
    - ```nntrainingdatatest.cpp``` *line 11*
    
- The project follows the Rule of 5.
    - ```nndata.h```
    - ```nndata.cpp```
    - ```nntrainingdata.h```
    - ```nntrainingdata.cpp```
    - ```nndatatest.h```
    - ```nndatatest.cpp```
    - ```nntrainingdatatest.h```
    - ```nntrainingdatatest.cpp```

### Conclusion

This project utilizes basic principles learned, such as dynamic memory and object oriented programming, to build a tool that can be used in future projects. Overall, I have been able to obtain a firm grasp of C++ programming and familiarize myself well with programming concepts.
