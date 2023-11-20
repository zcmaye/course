cmake_minimum_required(VERSION 3.2)
project(QtTest)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)

find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options("/Zc:__cplusplus")
endif()


add_executable(QtTest "main.cpp")

target_link_libraries(QtTest Qt6::Widgets Qt6::Charts)