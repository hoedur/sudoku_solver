cmake_minimum_required( VERSION 3.12 )

project( YetAnotherSudokuSolver LANGUAGES CXX )

message( STATUS "Sudoku Solver" )

add_executable ( sudoku_solver
    main.cpp
    board.cpp
)

set_property(TARGET sudoku_solver PROPERTY CXX_STANDARD 20)
