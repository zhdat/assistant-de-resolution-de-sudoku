cmake_minimum_required(VERSION 3.27)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Widgets REQUIRED)

include_directories(.)
target_link_libraries(Sudoku Qt5::Widgets)

add_executable(Sudoku
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        resources.qrc
        SudokuGrid.cpp
        SudokuGrid.h)
