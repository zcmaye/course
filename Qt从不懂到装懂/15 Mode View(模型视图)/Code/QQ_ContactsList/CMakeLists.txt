cmake_minimum_required(VERSION 3.8)

project("QQ_ContactsList")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS REQUIRED Widgets )


add_executable(QQ_ContactsList  "main.cpp" "ContactsAssets.qrc"
 "SContactsListView.h" "SContactsListView.cpp" "SContactsItemDelegate.h" "SContactsItemDelegate.cpp" "ContactsInfo.cpp" "ContactsInfo.h")

target_link_libraries(QQ_ContactsList Qt6::Widgets)