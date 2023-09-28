cmake_minimum_required(VERSION 3.5)

project(example VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

add_executable(signalAndSlots "parent_sub_widgetCut.cpp")  #父子窗口切换
add_executable(hello "login_demo.cpp")

target_link_libraries(signalAndSlots PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network)
target_link_libraries(hello PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network)

