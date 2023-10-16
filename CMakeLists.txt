cmake_minimum_required( VERSION 3.12 )

project( YetAnotherSudokuSolver LANGUAGES CXX )

message( STATUS "Sudoku Solver" )

# main executable
add_executable ( sudoku_solver
    main.cpp
    board.cpp
)
set_property(TARGET sudoku_solver PROPERTY CXX_STANDARD 20)

# unittests
add_subdirectory ( Catch2 )
add_executable ( unittest
    unittest.cpp
    board.cpp
)
set_property(TARGET unittest PROPERTY CXX_STANDARD 20)

target_link_libraries( unittest PRIVATE Catch2::Catch2WithMain )

