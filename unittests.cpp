#include <iostream>
#include <gtest/gtest.h>
#include "n_queens.h"

//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}

TEST(TDDTests, givenNothing_whenTrueConstant_thenAssertsTrue) {
    ASSERT_TRUE(true);
}

TEST(TDDTests, givenSizeLessThan4_whenCreatingBoard_thenFails) {
    try {
        new n_queens(3);
        FAIL();
    } catch (std::exception &ex) {
        ASSERT_TRUE( true);
    }
}

TEST(TDDTests, givenSizeOf4_whenCreatingBoard_thenCreatesBoardSizeBySize) {
    n_queens *solver = new n_queens(4);
    ASSERT_TRUE( solver != nullptr);
    board &board = solver->getBoard();
    ASSERT_EQ(4, board.getSquaresPerSide());
    delete solver;
}

TEST(TDDTests, givenSizeOf4AndAFixedQueenPositionInRange_whenCreatingBoard_thenFails) {
    square *fixedQueenPosition = new square(1, 3);
    n_queens *solver = new n_queens(4, fixedQueenPosition);
    ASSERT_TRUE( solver != nullptr);
    board &board = solver->getBoard();
    ASSERT_EQ(4, board.getSquaresPerSide());
    delete solver;
}

TEST(TDDTests, givenSizeOf4AndAFixedQueenPositionOutOfRange_whenCreatingBoard_thenCreatesBoardSizeBySize) {
    square *fixedQueenPosition = new square(2, 4);
    try {
        new n_queens(4, fixedQueenPosition);
        FAIL();
    } catch (std::exception &ex) {
        ASSERT_TRUE( true);
    }
}

