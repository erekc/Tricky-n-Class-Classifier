#include "gtest/gtest.h"
#include "../headers/common/spiralwalker.h"


class SpiralWalkerTest : public ::testing::Test{
protected:
    SpiralWalker spiralWalker = SpiralWalker();
};

TEST_F(SpiralWalkerTest, TestWalk){
    for (int i = 0; i < 25; ++i){
        spiralWalker.walk();
    }
    int* coords = spiralWalker.getCurrentPoint();
    EXPECT_EQ(coords[0], 2);
    EXPECT_EQ(coords[1], 3);
}