cmake_minimum_required(VERSION 3.2)

project(QsLog)

find_package(Qt NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)

set(QsLog_SOURCES 
    QsLogDest.cpp 
    QsLog.cpp 
    QsLogDestConsole.cpp 
    QsLogDestFile.cpp 
    QsLogDestFunctor.cpp
)

set(QsLog_HEADERS 
    QsLogDest.h 
    QsLog.h 
    QsLogDestConsole.h 
    QsLogLevel.h 
    QsLogDestFile.h 
    QsLogDisableForThisFile.h 
    QsLogDestFunctor.h
)

add_library(QsLog STATIC ${QsLog_SOURCES} )

target_include_directories(QsLog PRIVATE ${QsLog_HEADERS})

target_link_libraries(QsLog Qt${QT_VERSION_MAJOR}::Core)

