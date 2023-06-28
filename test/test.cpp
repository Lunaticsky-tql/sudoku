//
// Created by LENOVO on 2023/6/28.
//
// use Google test
#include "gtest/gtest.h"
#include "command.h"

TEST(ExceptionTest, TestInvalidArgs) {
    EXPECT_THROW(parseArgs(1, nullptr), ParseArgException);
    const char *argv1[2] = {"-c", "99999999"};
    EXPECT_THROW(parseArgs(3, argv1), ParseArgException);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}