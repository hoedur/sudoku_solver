#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <unordered_set>

class Board {
public:
    Board(const std::vector<int> & content) {
        this->content = std::move(content);
    }

    bool row_solved(unsigned int row) {
        std::unordered_set<int> seen;
        int first = row * Board::N_ROWS;
        int last = first + Board::N_COLS - 1;
        for (int idx = first; idx <= last; ++idx) {
            if (content[idx] == EMPTY_FIELD)
                return false;
            if (seen.insert(content[idx]).second == false)
                return false;
        }
        return true;
    }

    bool col_solved(unsigned int col) {
        std::unordered_set<int> seen;
        int first = col;
        int last = col + Board::N_COLS * (Board::N_ROWS - 1);
        for (int idx = first; idx <= last; idx += Board::N_COLS) {
            if (content[idx] == EMPTY_FIELD)
                return false;
            if (seen.insert(content[idx]).second == false)
                return false;
        }
        return true;
    }

    bool cluster_solved(unsigned int cluster) {
        std::unordered_set<int> seen;
        int first_row = (cluster / Board::CLUSTER_ROWS) * (Board::CLUSTER_ROWS);
        int last_row = first_row + Board::CLUSTER_ROWS - 1;
        int first_col = (cluster % Board::CLUSTER_COLS) * Board::CLUSTER_COLS;
        int last_col = first_col + Board::CLUSTER_COLS - 1;

        for (int i = first_row; i <= last_row; ++i) {
            for (int j = first_col; j <= last_col; ++j) {
                if (content[i * Board::N_ROWS + j] == Board::EMPTY_FIELD)
                    return false;
                if (seen.insert(content[i * Board::N_ROWS + j]).second == false)
                    return false;
            }
        }

        return true;
    }

    void print() {
        int row = 1;
        for (auto it = content.begin(); it != content.end(); ++it, ++row) {
            std::cout << *it;
            std::cout << (row % 9 == 0 ? '\n' : ' ');
        }
    }

    static const int EMPTY_FIELD;
    static const int N_ROWS;
    static const int N_COLS;
    static const int CLUSTER_ROWS;
    static const int CLUSTER_COLS;
private:
    std::vector<int> content;
};

const int Board::EMPTY_FIELD = 0;
const int Board::N_ROWS = 9;
const int Board::N_COLS = 9;
const int Board::CLUSTER_ROWS = 3;
const int Board::CLUSTER_COLS = 3;

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
    std::vector<int> board_content;
    char character;
    for (int i = 0; i < 81; ++i) {
        ifs >> character;
        int num = character - '0';
        board_content.push_back( (num >= 1 && num <= 9 ? num : Board::EMPTY_FIELD) );
    }

    Board b(board_content);
    b.print();

    for (int row = 0; row < Board::N_ROWS; ++row)
        std::cout << "Row " << row << " solved: " << b.row_solved(row) << '\n';
    for (int col = 0; col < Board::N_COLS; ++col)
        std::cout << "Col " << col << " solved: " << b.col_solved(col) << '\n';
    for (int cluster = 0; cluster < Board::CLUSTER_COLS * Board::CLUSTER_ROWS; ++cluster) {
        std::cout << "Clu " << cluster << " solved: " << b.cluster_solved(cluster) << '\n';
    }
}
