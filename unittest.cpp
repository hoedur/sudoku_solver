#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "board.hpp"

TEST_CASE( "Accessing the contents of a solved board" ) {
    std::vector<unsigned int> content = {
        5, 3, 4, 6, 7, 8, 9, 1, 2,
        6, 7, 2, 1, 9, 5, 3, 4, 8,
        1, 9, 8, 3, 4, 2, 5, 6, 7,
        8, 5, 9, 7, 6, 1, 4, 2, 3,
        4, 2, 6, 8, 5, 3, 7, 9, 1,
        7, 1, 3, 9, 2, 4, 8, 5, 6,
        9, 6, 1, 5, 3, 7, 2, 8, 4,
        2, 8, 7, 4, 1, 9, 6, 3, 5,
        3, 4, 5, 2, 8, 6, 1, 7, 9
    };
    Board b(content);
    const std::set<unsigned int> all_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    SECTION("Row by row index") {
        for (int i = 0; i < 9; ++i) {
            auto row = b.row_by_row_index(i);
            REQUIRE(row == all_numbers);
        }
    }

    SECTION("Column by column index") {
        for (int i = 0; i < 9; ++i) {
            auto col = b.col_by_col_index(i);
            REQUIRE(col == all_numbers);
        }
    }

    SECTION("Block by block index") {
        for (int i = 0; i < 9; ++i) {
            auto block = b.col_by_col_index(i);
            REQUIRE(block == all_numbers);
        }
    }
}
