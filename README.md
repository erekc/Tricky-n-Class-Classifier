# Tricky n Class Classifier Data Generation

### Introduction

In exploring many of the project options, I decided to pursue one that stems from my experience in Intelligent Systems, particularly Multilayer Perceptrons. In brainstorming for my project, I decided that I wanted to pursue the construction of a simple 2-dimensional n-Class classifying MLP, which given data points, would predict the class of a 2d input vector. To do this, I first needed a way to generate random data so that the predictions can be graphed in a dense, regional manner. From this requirement came the inception of this project: creating a set of classes that can collectively generate different kinds of data and display the results. This idea was perfect for me, as this gives a great intro to C++ and is an involved way to build something upon which I can not only build more features, such as the MLP itself, but also continue to sharpen and strengthen my C++ skills. This project has been a fun way for me to not only complete my first C++ project, but also give me an introduction into the expansive world of C++.

### Installation, Build, & Run

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
