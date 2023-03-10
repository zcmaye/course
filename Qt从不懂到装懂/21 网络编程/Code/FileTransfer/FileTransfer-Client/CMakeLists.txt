cmake_minimum_required(VERSION 3.8)

project(FileTransfer-Client)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Network REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin)

add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)

aux_source_directory(. MY_SOURCES)

set(UI_FILES "MainWindow.ui")
qt_wrap_ui(${PROJECT_NAME} ${UI_FILES})
include_directories(${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${MY_SOURCES} ${UI_FILES})

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Network)