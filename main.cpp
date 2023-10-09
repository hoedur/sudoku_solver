#include <cassert>
#include <exception>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <set>

class Board {
public:
    Board(const std::vector<unsigned int> & content) {
        this->content = std::move(content);
    }

    class OutOfBoundsException : public std::exception
    {
    public:
        virtual const char* what() const noexcept override  {
            return "Out of bounds access";
        }
    };

    std::set<unsigned int> row_by_row_index(unsigned int idx) {
        if (idx >= Board::N_ROWS)
             throw OutOfBoundsException();

        std::set<unsigned int> result;
        int first = idx * Board::N_ROWS;
        int last = first + Board::N_COLS - 1;

        for (int i = first; i <= last; ++i)
            result.insert(content[i]);

        return result;
    }

    std::set<unsigned int> col_by_col_index(unsigned int idx) {
        if (idx > Board::N_ROWS)
            throw OutOfBoundsException();

        std::set<unsigned int> result;
        int first = idx;
        int last = idx + Board::N_COLS * (Board::N_ROWS - 1);
        for (int i = first; i <= last; i += Board::N_ROWS)
            result.insert(content[i]);

        return result;
    }

    std::set<unsigned int> block_by_block_index (unsigned int idx) {
        std::set<unsigned int> result;
        int first_row = (idx / Board::N_BLOCK_ROWS) * (Board::N_BLOCK_ROWS);
        int last_row = first_row + Board::N_BLOCK_ROWS - 1;
        int first_col = (idx % Board::N_BLOCK_COLS) * Board::N_BLOCK_COLS;
        int last_col = first_col + Board::N_BLOCK_COLS - 1;

        for (int i = first_row; i <= last_row; ++i) {
            for (int j = first_col; j <= last_col; ++j) {
                result.insert(content[i * Board::N_ROWS + j]);
            }
        }

        return result;
    }

    unsigned int index_to_row(unsigned int idx)
    {
        if (idx > Board::N_ELEMENTS)
            throw OutOfBoundsException();

        return idx / Board::N_COLS;
    }

    unsigned int index_to_col(unsigned int idx)
    {
        if (idx > Board::N_ELEMENTS)
            throw OutOfBoundsException();

        return idx % Board::N_ROWS;
    }

    unsigned int index_to_block(unsigned int idx)
    {
        if (idx > Board::N_ELEMENTS)
            throw OutOfBoundsException();

        return index_to_col(idx) + Board::N_BLOCK_ROWS * (index_to_row(idx) % Board::N_BLOCK_ROWS);
    }

    bool row_solved(unsigned int row_idx) {
        auto row = row_by_row_index(row_idx);
        if (row.contains(Board::EMPTY_FIELD) || row.size() != Board::N_COLS)
            return false;
        else
            return true;
    }

    bool col_solved(unsigned int col_idx) {
        auto col = col_by_col_index(col_idx);
        if (col.contains(Board::EMPTY_FIELD) || col.size() != Board::N_ROWS)
            return false;
        else
            return true;
    }

    bool block_solved(unsigned int block_idx) {
        auto block = block_by_block_index(block_idx);
        if (block.contains(Board::EMPTY_FIELD) || block.size() != Board::N_BLOCK_ELEMENTS)
            return false;
        else
            return true;
    }

    void print() {
        int row = 1;
        for (auto it = content.begin(); it != content.end(); ++it, ++row) {
            std::cout << *it;
            std::cout << (row % 9 == 0 ? '\n' : ' ');
        }
    }

    std::set<unsigned int> missing_numbers(unsigned int idx)
    {
        std::set<unsigned int> result;

        auto row = row_by_row_index(index_to_row(idx));
        for (unsigned int i = 0; i < Board::N_ROWS; ++i) {
            if (!row.contains(i)) {
                result.insert(i);
            }
        }

        auto col = col_by_col_index(index_to_col(idx));
        for (unsigned int i = 0; i < Board::N_COLS; ++i) {
            if (!col.contains(i))
                result.insert(i);
        }

        auto block = block_by_block_index(index_to_block(idx));
        for (unsigned int i = 0; i < Board::N_BLOCK_ELEMENTS; ++i) {
            if (!col.contains(i))
                result.insert(i);
        }

        return result;
    }

    std::vector<unsigned int> solve_recursive(std::vector<unsigned int> _content)
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

    static const unsigned int EMPTY_FIELD;
    static const unsigned int N_ROWS;
    static const unsigned int N_COLS;
    static const unsigned int N_ELEMENTS;
    static const unsigned int N_BLOCK_ROWS;
    static const unsigned int N_BLOCK_COLS;
    static const unsigned int N_BLOCK_ELEMENTS;

    std::vector<unsigned int> content;
};

const unsigned int Board::EMPTY_FIELD = 0;
const unsigned int Board::N_ROWS = 9;
const unsigned int Board::N_COLS = 9;
const unsigned int Board::N_ELEMENTS = Board::N_ROWS * N_COLS;
const unsigned int Board::N_BLOCK_ROWS = 3;
const unsigned int Board::N_BLOCK_COLS = 3;
const unsigned int Board::N_BLOCK_ELEMENTS = Board::N_BLOCK_ROWS * Board::N_BLOCK_COLS;

void error_exit(int e, std::string m = "")
{
    std::cout << "Error" << (m.length() > 0 ? std::string(": " + m) : std::string("")) << '\n';
    exit(e);
}

int main(int argc, char** argv)
{
    if (argc != 2)
        error_exit(1, "Synopsis: \n\t" + std::string(argv[0]) + " filename");

    std::filesystem::path p(argv[1]);
    if (!std::filesystem::exists(p))
        error_exit(1, "File " + std::string(p) + " does not exist.");

    std::ifstream ifs(p, std::ios::in);
    std::vector<unsigned int> board_content;
    char character;
    for (unsigned int i = 0; i < 81; ++i) {
        ifs >> character;
        unsigned int num = character - '0';
        board_content.push_back( (num >= 1 && num <= 9 ? num : Board::EMPTY_FIELD) );
    }

    Board b(board_content);
    b.print();
    b.solve_recursive(b.content);

    for (unsigned int row = 0; row < Board::N_ROWS; ++row) {
        std::cout << "Row " << row << " solved: " << b.row_solved(row) << '\n';
    }
    for (unsigned int col = 0; col < Board::N_COLS; ++col) {
        std::cout << "Col " << col << " solved: " << b.col_solved(col) << '\n';
    }
    for (unsigned int block = 0; block < Board::N_BLOCK_COLS * Board::N_BLOCK_ROWS; ++block) {
        std::cout << "Clu " << block << " solved: " << b.block_solved(block) << '\n';
    }

    try {
        b.row_by_row_index(9);
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
