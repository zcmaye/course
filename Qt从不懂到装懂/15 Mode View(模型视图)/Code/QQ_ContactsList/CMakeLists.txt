cmake_minimum_required(VERSION 3.8)

project("QQ_ContactsList")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS REQUIRED Widgets )

#aux_source_directory(./SCustomWidgets SRC_Widgets)
add_executable(QQ_ContactsList  
"main.cpp" "ContactsAssets.qrc"
 "SCustomWidgets/SListView.h" "SContactsListView.cpp" 
 "SContactsItemDelegate.h" "SContactsItemDelegate.cpp" 
 "ContactsInfo.cpp" "ContactsInfo.h" 
 "SCustomWidgets/SItemDelegate.cpp" 
 "SCustomWidgets/SItemDelegate.h" 
 "SCustomWidgets/SListView.cpp" 
 "SCustomWidgets/SListView.h")

target_link_libraries(QQ_ContactsList Qt6::Widgets)