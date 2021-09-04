#include <iostream>
#include <gtest/gtest.h>
#include "n_queens.h"

#if 0
int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    auto returnValue = solveNQueens(4, {1, 0});
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Result is: " << returnValue << std::endl;
    return 0;
}
#endif

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

//TEST(TDDTests, givenBoardSize8_whenPlacing2QueensOnSameRow_thenReturnsPressureOf1OnTargetQueen) {
//    auto *fixedQueenPosition = new square(2, 4);
//    auto *sut = new n_queens(8, fixedQueenPosition);
//    auto board = sut->getBoard();
//    auto *weights = board.getWeights(4);
//    ASSERT_EQ(1, weights->getWeightFor(4));
//}

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

TEST(TDDTests, givenBoardSize8WithPlacedQueen_whenSolvingProblem_thenReturnsSolutionString) {
    auto returnValue = solveNQueens(8, {1, 0});
    ASSERT_TRUE(returnValue.length() > 0);
}

TEST(TDDTests, givenBoardSize16WithPlacedQueen_whenSolvingProblem_thenReturnsSolutionString) {
    auto returnValue = solveNQueens(16, {1, 0});
    ASSERT_TRUE(returnValue.length() > 0);
}

TEST(TDDTests, givenBoardSize24WithPlacedQueen_whenSolvingProblem_thenReturnsSolutionString) {
    auto returnValue = solveNQueens(24, {1, 0});
    ASSERT_TRUE(returnValue.length() > 0);
}

TEST(TDDTests, givenBoardSize32WithPlacedQueen_whenSolvingProblem_thenReturnsSolutionString) {
    auto returnValue = solveNQueens(32, {1, 0});
    ASSERT_TRUE(returnValue.length() > 0);
}
