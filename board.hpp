#pragma once

#include <cassert>
#include <exception>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class Board {
public:
    Board(const std::vector<unsigned int> & content);

    class OutOfBoundsException : public std::exception
    {
    public:
        virtual const char* what() const noexcept override;
    };

    std::set<unsigned int> row_by_row_index(unsigned int idx);

    std::set<unsigned int> col_by_col_index(unsigned int idx);

    std::set<unsigned int> block_by_block_index (unsigned int idx);

    unsigned int index_to_row(unsigned int idx);

    unsigned int index_to_col(unsigned int idx);

    unsigned int index_to_block(unsigned int idx);

    bool row_solved(unsigned int row_idx);

    bool col_solved(unsigned int col_idx);

    bool block_solved(unsigned int block_idx);

    void print();

    std::set<unsigned int> missing_numbers(unsigned int idx);

    std::vector<unsigned int> solve_recursive(std::vector<unsigned int> _content);

    static const unsigned int EMPTY_FIELD;
    static const unsigned int N_ROWS;
    static const unsigned int N_COLS;
    static const unsigned int N_ELEMENTS;
    static const unsigned int N_BLOCK_ROWS;
    static const unsigned int N_BLOCK_COLS;
    static const unsigned int N_BLOCK_ELEMENTS;

    std::vector<unsigned int> content;
};

