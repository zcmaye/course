# CMakeLists.txt for QCustomPlot Library
cmake_minimum_required(VERSION 3.20)

project(QCustomPlot LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets PrintSupport REQUIRED)

set(QCUSTOMPLOT_HEADERS "qcustomplot.h")
set(QCUSTOMPLOT_SOURCES "qcustomplot.cpp")

add_library(${PROJECT_NAME} STATIC ${QCUSTOMPLOT_SOURCES})

target_link_libraries(${PROJECT_NAME}  PUBLIC Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
