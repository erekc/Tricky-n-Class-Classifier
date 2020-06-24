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

file(GLOB MAIN_SOURCES "src/main/*")
file(GLOB TEST_SOURCES "src/test/*")
file(GLOB COMMON_SOURCES "src/common/*")
file(GLOB MAIN_HEADERS "headers/main/*")
file(GLOB TEST_HEADERS "headers/test/*")
file(GLOB COMMON_HEADERS "headers/common/*")

add_executable(Tricky-n-Class-Classifier
  ${MAIN_SOURCES}
  ${COMMON_SOURCES}
  ${MAIN_HEADERS}
  ${COMMON_HEADERS}
)

add_executable(test
    ${TEST_SOURCES}
    ${TEST_HEADERS}
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
)

add_subdirectory(thirdparty/googletest)

add_executable(utest
  test/utest_datagen.cpp
  ${COMMON_SOURCES}
  ${COMMON_HEADERS}
)

target_link_libraries(utest gtest_main)

target_include_directories(Tricky-n-Class-Classifier PUBLIC ${xtensor_INCLUDE_DIRS})
target_link_libraries(Tricky-n-Class-Classifier PUBLIC xtensor PRIVATE Qt5::Core Qt5::Widgets Qt5::Charts Qt5::Gui)
target_include_directories(test PUBLIC ${xtensor_INCLUDE_DIRS})
target_link_libraries(test PUBLIC xtensor)
