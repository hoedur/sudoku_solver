#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "board.hpp"

TEST_CASE( "Accessing the contents of a solved board" ) {
    /*
     *  00 01 02 03 04 05 06 07 08
     *  09 10 11 12 13 14 15 16 17
     *  18 19 20 21 22 23 24 25 26
     *  27 28 29 30 31 32 33 34 35
     *  36 37 38 39 40 41 42 43 44
     *  45 46 47 48 49 50 51 52 53
     *  54 55 56 57 58 59 60 61 62
     *  63 64 65 66 67 68 69 70 71
     *  72 73 74 75 76 77 78 79 80
     */

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

    SECTION("Boundary test: Resolve index to row 0") {
        REQUIRE(b.index_to_row(0) == 0);
        REQUIRE(b.index_to_row(8) == 0);
    }

    SECTION("Boundary test: Resolve index to row 1") {
        REQUIRE(b.index_to_row(9) == 1);
        REQUIRE(b.index_to_row(17) == 1);
    }

    SECTION("Boundary test: Resolve index to row 2") {
        REQUIRE(b.index_to_row(18) == 2);
        REQUIRE(b.index_to_row(26) == 2);
    }

    SECTION("Boundary test: Resolve index to row 3") {
        REQUIRE(b.index_to_row(27) == 3);
        REQUIRE(b.index_to_row(35) == 3);
    }

    SECTION("Boundary test: Resolve index to row 4") {
        REQUIRE(b.index_to_row(36) == 4);
        REQUIRE(b.index_to_row(44) == 4);
    }

    SECTION("Boundary test: Resolve index to row 5") {
        REQUIRE(b.index_to_row(45) == 5);
        REQUIRE(b.index_to_row(53) == 5);
    }

    SECTION("Boundary test: Resolve index to row 6") {
        REQUIRE(b.index_to_row(54) == 6);
        REQUIRE(b.index_to_row(62) == 6);
    }

    SECTION("Boundary test: Resolve index to row 7") {
        REQUIRE(b.index_to_row(63) == 7);
        REQUIRE(b.index_to_row(71) == 7);
    }

    SECTION("Boundary test: Resolve index to row 8") {
        REQUIRE(b.index_to_row(72) == 8);
        REQUIRE(b.index_to_row(80) == 8);
    }

    SECTION("Boundary test: Resolve index to col 0") {
        REQUIRE(b.index_to_col(0) == 0);
        REQUIRE(b.index_to_col(72) == 0);
    }

    SECTION("Boundary test: Resolve index to col 1") {
        REQUIRE(b.index_to_col(1) == 1);
        REQUIRE(b.index_to_col(73) == 1);
    }

    SECTION("Boundary test: Resolve index to col 2") {
        REQUIRE(b.index_to_col(2) == 2);
        REQUIRE(b.index_to_col(74) == 2);
    }

    SECTION("Boundary test: Resolve index to col 3") {
        REQUIRE(b.index_to_col(3) == 3);
        REQUIRE(b.index_to_col(75) == 3);
    }

    SECTION("Boundary test: Resolve index to col 4") {
        REQUIRE(b.index_to_col(4) == 4);
        REQUIRE(b.index_to_col(76) == 4);
    }

    SECTION("Boundary test: Resolve index to col 5") {
        REQUIRE(b.index_to_col(5) == 5);
        REQUIRE(b.index_to_col(77) == 5);
    }

    SECTION("Boundary test: Resolve index to col 6") {
        REQUIRE(b.index_to_col(6) == 6);
        REQUIRE(b.index_to_col(78) == 6);
    }

    SECTION("Boundary test: Resolve index to col 7") {
        REQUIRE(b.index_to_col(7) == 7);
        REQUIRE(b.index_to_col(79) == 7);
    }

    SECTION("Boundary test: Resolve index to col 8") {
        REQUIRE(b.index_to_col(8) == 8);
        REQUIRE(b.index_to_col(80) == 8);
    }

    SECTION("Resolve index to block 0") {
        REQUIRE(b.index_to_block(0) == 0);
        REQUIRE(b.index_to_block(2) == 0);
        REQUIRE(b.index_to_block(18) == 0);
        REQUIRE(b.index_to_block(20) == 0);
    }

    SECTION("Resolve index to block 1") {
        REQUIRE(b.index_to_block(3) == 1);
        REQUIRE(b.index_to_block(5) == 1);
        REQUIRE(b.index_to_block(21) == 1);
        REQUIRE(b.index_to_block(23) == 1);
    }

    SECTION("Resolve index to block 2") {
        REQUIRE(b.index_to_block(6) == 2);
        REQUIRE(b.index_to_block(8) == 2);
        REQUIRE(b.index_to_block(24) == 2);
        REQUIRE(b.index_to_block(26) == 2);
    }

    SECTION("Resolve index to block 3") {
        REQUIRE(b.index_to_block(27) == 3);
        REQUIRE(b.index_to_block(29) == 3);
        REQUIRE(b.index_to_block(45) == 3);
        REQUIRE(b.index_to_block(47) == 3);
    }

    SECTION("Resolve index to block 4") {
        REQUIRE(b.index_to_block(30) == 4);
        REQUIRE(b.index_to_block(32) == 4);
        REQUIRE(b.index_to_block(48) == 4);
        REQUIRE(b.index_to_block(50) == 4);
    }

    SECTION("Resolve index to block 5") {
        REQUIRE(b.index_to_block(33) == 5);
        REQUIRE(b.index_to_block(35) == 5);
        REQUIRE(b.index_to_block(51) == 5);
        REQUIRE(b.index_to_block(53) == 5);
    }

    SECTION("Resolve index to block 6") {
        REQUIRE(b.index_to_block(54) == 6);
        REQUIRE(b.index_to_block(56) == 6);
        REQUIRE(b.index_to_block(72) == 6);
        REQUIRE(b.index_to_block(74) == 6);
    }

    SECTION("Resolve index to block 7") {
        REQUIRE(b.index_to_block(57) == 7);
        REQUIRE(b.index_to_block(59) == 7);
        REQUIRE(b.index_to_block(75) == 7);
        REQUIRE(b.index_to_block(77) == 7);
    }

    SECTION("Resolve index to block 8") {
        REQUIRE(b.index_to_block(60) == 8);
        REQUIRE(b.index_to_block(62) == 8);
        REQUIRE(b.index_to_block(78) == 8);
        REQUIRE(b.index_to_block(80) == 8);
    }
}

TEST_CASE( "Check for solved rows, columns and blocks" ) {
    std::vector<unsigned int> content_all_zeros = {};
    for (int i = 0; i < 81; ++i) {
        content_all_zeros.push_back(0);
    }
    Board b_all_zeros(content_all_zeros);

    SECTION("Board with all zeros") {
        for (int row_id = 0; row_id < Board::N_ROWS; ++row_id) {
            REQUIRE(b_all_zeros.row_solved(row_id) == false);
        }

        for (int col_id = 0; col_id < Board::N_COLS; ++col_id) {
            REQUIRE(b_all_zeros.col_solved(col_id) == false);
        }

        for (int block_id = 0; block_id < Board::N_BLOCKS; ++block_id) {
            REQUIRE(b_all_zeros.block_solved(block_id) == false);
        }
    }
}
