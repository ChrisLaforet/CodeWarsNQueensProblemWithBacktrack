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

TEST(TDDTests, givenSizeLessThan4_whenCreatingBoard_thenReturnsNull) {
    ASSERT_TRUE(createNQueens(3) == nullptr);
}


TEST(TDDTests, givenSizeOf4_whenCreatingBoard_thenCreatesBoardSizeBySize) {
    ASSERT_TRUE( createNQueens(4) != nullptr);
}

