//
// Created by LENOVO on 2023/6/28.
//
// use Google test
#include "gtest/gtest.h"
#include "command.h"

bool testLegalSolutionMap(Board board) {
    int i, j, k, l, m;
    for (i = 0; i < 9; i++) {
        for (j = 1; j <= 9; j++) {
            for (k = 0; k < 9; k++) {
                if (board[i][k] == j)
                    break;
            }
            if (k == 9) {
                print_error("Board Error:Raw Error\n");
                return false;
            }


            for (l = 0; l < 9; l++) {
                if (board[l][i] == j)
                    break;
            }
            if (l == 9) {
                print_error("Board Error:Col Error\n");
                return false;
            }

        }

    }
    for (i = 0; i < 9; i += 3) {
        for (j = 0; j < 9; j += 3) {
            for (k = 1; k <= 9; k++) {
                for (l = i; l < i + 3; l++) {
                    for (m = j; m < j + 3; m++) {
                        if (board[l][m] == k)
                            break;
                    }
                    if (board[l][m] == k)
                        break;
                }
                if (l == i + 3) {
                    print_error("Board Error:3*3 Error\n");
                    return false;
                }
            }
        }
    }
    return true;
}

TEST(ExceptionTest, TestInvalidArgs) {
    EXPECT_THROW(parseArgs(1, nullptr), ParseArgException);
    const char *argv1[2] = {"-c", "99999999"};
    EXPECT_THROW(parseArgs(3, argv1), ParseArgException);
}

TEST(GenerateMapTest, TestSolutionMap) {
    vector<Board> map = mapGenerate(10);
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(testLegalSolutionMap(map[i]));
    }
}

TEST(GenerateMapTest, TestMapReadAndWrite) {
    vector<Board> map = mapGenerate(10);
    EXPECT_TRUE(writeBoards2File(map, SOLUTION_MAP_PATH));
    std::ifstream fp(SOLUTION_MAP_PATH);
    int size;
    fp >> size;
    EXPECT_EQ(size, 10);
    Board board;
    for (int i = 0; i < 10; i++) {
        board.readBoard(fp);
        EXPECT_TRUE(testLegalSolutionMap(board));
    }

}

// TEST(GenerateQuestionTest, TestQuestions) {
//    int n = 10;
//    for(n=10;n<=40;n+=5)
//    {
//        EXPECT_THROW(mapGenerate(n), ParseArgException);
//        EXPECT_THROW(generateQuesN(n), ParseArgException);
//        EXPECT_THROW(generateQuesM(n,1), ParseArgException);
//        EXPECT_THROW(generateQuesM(n,2), ParseArgException);
//        EXPECT_THROW(generateQuesM(n,3), ParseArgException);
//    }
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
