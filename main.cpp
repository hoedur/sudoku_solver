#include "board.hpp"

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
