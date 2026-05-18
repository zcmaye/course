cmake_minimum_required(VERSION 3.16)
project(test_qt_sql LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Sql
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    User.h
    UserDao.h
    UserDao.cpp
    test_user_dao.cpp
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Sql
)

