cmake_minimum_required(VERSION 3.8)

project(QtProject)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)

aux_source_directory(. MY_SOURCES)
add_executable(QtProject ${MY_SOURCES} "main.cpp" "SItemCheckDelegate.cpp" "SItemCheckDelegate.h")
target_link_libraries(QtProject Qt6::Widgets)