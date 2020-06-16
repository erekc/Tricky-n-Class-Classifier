cmake_minimum_required(VERSION 3.5)

project(Tricky-n-Class-Classifier LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "/home/erekryo/Qt5.14.2/5.14.2/gcc_64/lib/cmake/")
set(xtensor_DIR "/usr/local/include")
set(xtl_DIR "/usr/local/include")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(xtensor REQUIRED)
find_package(xtl REQUIRED)
find_package(Qt5 COMPONENTS Widgets Core Charts Gui REQUIRED)

add_executable(Tricky-n-Class-Classifier
  main.cpp
  chartview.cpp
  chartview.h
  nndata.cpp
  nndata.h
  nntrainingdata.cpp
  nntrainingdata.h
)

target_include_directories(Tricky-n-Class-Classifier PUBLIC ${xtensor_INCLUDE_DIRS})
target_link_libraries(Tricky-n-Class-Classifier PUBLIC xtensor PRIVATE Qt5::Core Qt5::Widgets Qt5::Charts Qt5::Gui)
