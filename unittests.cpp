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
    auto *solver = new n_queens(4);
    ASSERT_TRUE( solver != nullptr);
    board &board = solver->getBoard();
    ASSERT_EQ(4, board.getSquaresPerSide());
    delete solver;
}

TEST(TDDTests, givenSizeOf4AndAFixedQueenPositionInRange_whenCreatingBoard_thenFails) {
    auto *fixedQueenPosition = new square(1, 3);
    auto *solver = new n_queens(4, fixedQueenPosition);
    ASSERT_TRUE( solver != nullptr);
    board &board = solver->getBoard();
    ASSERT_EQ(4, board.getSquaresPerSide());
    delete solver;
}

TEST(TDDTests, givenSizeOf4AndAFixedQueenPositionOutOfRange_whenCreatingBoard_thenCreatesBoardSizeBySize) {
    auto *fixedQueenPosition = new square(2, 4);
    try {
        new n_queens(4, fixedQueenPosition);
        FAIL();
    } catch (std::exception &ex) {
        ASSERT_TRUE( true);
    }
}

TEST(TDDTests, givenBoardSize8_whenPlacing2QueensOnSameRow_thenReturnsPressureOf1OnTargetQueen) {
    auto *fixedQueenPosition = new square(2, 4);
    auto *sut = new n_queens(8, fixedQueenPosition);
    auto board = sut->getBoard();
    auto *weights = board.getWeights(4);
    ASSERT_EQ(1, weights->getWeightFor(4));
}

TEST(TDDTests, givenBoardSize8_whenPlacingQueen_thenReturnsRowsWithoutQueen) {
    auto *fixedQueenPosition = new square(2, 4);
    auto *sut = new n_queens(8, fixedQueenPosition);
    auto board = sut->getBoard();
    int columnCount = 0;
    auto columns = board.getColumnsWithoutQueens(columnCount);
    ASSERT_EQ(7, columnCount);
}

TEST(TDDTests, givenBoardSize4WithPlacedQueen_whenSolvingProblem_thenReturnsSolutionString) {
    auto returnValue = solveNQueens(4, {1, 0});
    ASSERT_TRUE(returnValue.length() > 0);
}


