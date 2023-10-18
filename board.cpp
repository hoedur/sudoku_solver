#include "board.hpp"

Board::Board(const std::vector<unsigned int> & content) {
    this->content = std::move(content);
}

const char* Board::Board::OutOfBoundsException::what() const noexcept {
    return "Out of bounds access";
}


std::set<unsigned int> Board::row_by_row_index(unsigned int idx) {
    if (idx >= Board::N_ROWS)
         throw OutOfBoundsException();

    std::set<unsigned int> result;
    int first = idx * Board::N_ROWS;
    int last = first + Board::N_COLS - 1;

    for (int i = first; i <= last; ++i) {
        if (content[i] == Board::EMPTY_FIELD)
            continue;
        result.insert(content[i]);
    }

    return result;
}

std::set<unsigned int> Board::col_by_col_index(unsigned int idx) {
    if (idx > Board::N_ROWS)
        throw OutOfBoundsException();

    std::set<unsigned int> result;
    int first = idx;
    int last = idx + Board::N_COLS * (Board::N_ROWS - 1);
    for (int i = first; i <= last; i += Board::N_ROWS) {
        if (content[i] == Board::EMPTY_FIELD)
            continue;
        result.insert(content[i]);
    }

    return result;
}

std::set<unsigned int> Board::block_by_block_index (unsigned int idx) {
    std::set<unsigned int> result;
    int first_row = (idx / Board::N_BLOCK_ROWS) * (Board::N_BLOCK_ROWS);
    int last_row = first_row + Board::N_BLOCK_ROWS - 1;
    int first_col = (idx % Board::N_BLOCK_COLS) * Board::N_BLOCK_COLS;
    int last_col = first_col + Board::N_BLOCK_COLS - 1;

    for (int i = first_row; i <= last_row; ++i) {
        for (int j = first_col; j <= last_col; ++j) {
            unsigned int val = content[i * Board::N_ROWS + j];
            if (val == Board::EMPTY_FIELD)
                continue;
            result.insert(val);
        }
    }

    return result;
}

unsigned int Board::index_to_row(unsigned int idx)
{
    if (idx > Board::N_ELEMENTS)
        throw OutOfBoundsException();

    return idx / Board::N_COLS;
}

unsigned int Board::index_to_col(unsigned int idx)
{
    if (idx > Board::N_ELEMENTS)
        throw OutOfBoundsException();

    return idx % Board::N_ROWS;
}

unsigned int Board::index_to_block(unsigned int idx)
{
    if (idx > Board::N_ELEMENTS)
        throw OutOfBoundsException();

    return (index_to_col(idx) / Board::N_BLOCK_COLS)
           + Board::N_BLOCK_ROWS * (index_to_row(idx) / Board::N_BLOCK_ROWS);
}

bool Board::row_solved(unsigned int row_idx) {
    auto row = row_by_row_index(row_idx);
    if (row.contains(Board::EMPTY_FIELD) || row.size() != Board::N_COLS)
        return false;
    else
        return true;
}

bool Board::col_solved(unsigned int col_idx) {
    auto col = col_by_col_index(col_idx);
    if (col.contains(Board::EMPTY_FIELD) || col.size() != Board::N_ROWS)
        return false;
    else
        return true;
}

bool Board::block_solved(unsigned int block_idx) {
    auto block = block_by_block_index(block_idx);
    if (block.contains(Board::EMPTY_FIELD) || block.size() != Board::N_BLOCK_ELEMENTS)
        return false;
    else
        return true;
}

void Board::print() {
    int row = 1;
    for (auto it = content.begin(); it != content.end(); ++it, ++row) {
        std::cout << *it;
        std::cout << (row % 9 == 0 ? '\n' : ' ');
    }
}

// XXX Buggy!
std::set<unsigned int> Board::missing_numbers(unsigned int idx)
{
    std::set<unsigned int> row_col, row_col_block, result;
    std::vector<unsigned int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto row = row_by_row_index(index_to_row(idx));
    for (auto it : row) std::cout << it << ' ';
    std::cout << std::endl;
    auto col = col_by_col_index(index_to_col(idx));
    for (auto it : col) std::cout << it << ' ';
    std::cout << std::endl;
    auto block = block_by_block_index(index_to_block(idx));
    for (auto it : block) std::cout << it << ' ';
    std::cout << std::endl;

    std::set_union(row.begin(), row.end(), col.begin(), col.end(),
        std::inserter(row_col, row_col.begin()));
    for (auto it : row_col) std::cout << it << ' ';
    std::cout << std::endl;

    std::set_union(row_col.begin(), row_col.end(), block.begin(), block.end(),
        std::inserter(row_col_block, row_col_block.begin()));
    for (auto it : row_col_block) std::cout << it << ' ';
    std::cout << std::endl;

    std::set_difference(row_col_block.begin(), row_col_block.end(), all.begin(), all.end(),
        std::inserter(result, result.begin()));

    return result;
}

std::vector<unsigned int> Board::solve_recursive(std::vector<unsigned int> _content)
{
    for (unsigned int idx = 0; idx < _content.size(); ++idx) {
        if (_content[idx] == Board::EMPTY_FIELD) {
            std::cout << "empty field at index " << idx << '\n';
            auto missing = missing_numbers(idx);

            std::cout << missing.size() << " numbers are missing: ";
            for (auto it = missing.begin(); it != missing.end(); ++it) {
                std::cout << *it << ' ';
            }
            std::cout << '\n';
        }
    }

    return std::vector<unsigned int>(); // XXX
}

const unsigned int Board::EMPTY_FIELD = 0;
const unsigned int Board::N_ROWS = 9;
const unsigned int Board::N_COLS = 9;
const unsigned int Board::N_ELEMENTS = Board::N_ROWS * N_COLS;
const unsigned int Board::N_BLOCKS = Board::N_ELEMENTS / Board::N_BLOCK_ELEMENTS;
const unsigned int Board::N_BLOCK_ROWS = 3;
const unsigned int Board::N_BLOCK_COLS = 3;
const unsigned int Board::N_BLOCK_ELEMENTS = Board::N_BLOCK_ROWS * Board::N_BLOCK_COLS;
