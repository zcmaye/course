cmake_minimum_required(VERSION 3.8)

project(FileTransfer-Server)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS  Network REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin)

add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)

aux_source_directory(. MY_SOURCES)
add_executable(${PROJECT_NAME} ${MY_SOURCES} )
target_link_libraries(${PROJECT_NAME} Qt6::Network)