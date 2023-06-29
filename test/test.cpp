//
// Created by LENOVO on 2023/6/28.
//
// use Google test
#include "gtest/gtest.h"
#include "command.h"

bool testLegalSolutionMap(Board board)
{
    int i, j, k, l, m;
    for (i = 0; i < 9; i++)
    {
        for (j = 1; j <= 9; j++)
        {
            for (k = 0; k < 9; k++)
            {
                if (board[i][k] == j)
                    break;
            }
            if (k == 9)
            {
                print_error("Board Error:Raw Error\n");
                return false;
            }
            for (l = 0; l < 9; l++)
            {
                if (board[l][i] == j)
                    break;
            }
            if (l == 9)
            {
                print_error("Board Error:Col Error\n");
                return false;
            }
        }
    }
    for (i = 0; i < 9; i += 3)
    {
        for (j = 0; j < 9; j += 3)
        {
            for (k = 1; k <= 9; k++)
            {
                for (l = i; l < i + 3; l++)
                {
                    for (m = j; m < j + 3; m++)
                    {
                        if (board[l][m] == k)
                            break;
                    }
                    if (board[l][m] == k)
                        break;
                }
                if (l == i + 3)
                {
                    print_error("Board Error:3*3 Error\n");
                    return false;
                }
            }
        }
    }
    return true;
}

bool testRightCountOfBlank(Board &board, const std::pair<int, int> &blank)
{
    int i, j;
    int count = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (board[i][j] == 0)
                count++;
        }
    }
    std::cout << count << std::endl;
    return count >= blank.first && count <= blank.second;
}
TEST(ExceptionTest, TestInvalidArgs)
{
    const char *argv1[1] = {"sudoku.exe"};
    EXPECT_THROW(parseArgs(1, argv1), ParseArgException);
    const char *argv2[2] = {"sudoku.exe", "-c"};
    EXPECT_THROW(parseArgs(2, argv2), ParseArgException);
    const char *argv3[3] = {"sudoku.exe", "-c", "99999999"};
    EXPECT_THROW(parseArgs(3, argv3), ParseArgException);
    const char *argv4[2] = {"sudoku.exe", "-s"};
    EXPECT_THROW(parseArgs(2, argv4), ParseArgException);
    const char *argv5[3] = {"sudoku.exe", "-s", "nonexistent.txt"};
    EXPECT_THROW(parseArgs(3, argv5), ParseArgException);
    const char *argv6[3] = {"sudoku.exe", "-n", "0"};
    EXPECT_THROW(parseArgs(3, argv6), ParseArgException);
    const char *argv7[3] = {"sudoku.exe", "-n", "10001"};
    EXPECT_THROW(parseArgs(3, argv7), ParseArgException);
    const char *argv8[5] = {"sudoku.exe", "-n", "1000", "-m", "0"};
    EXPECT_THROW(parseArgs(5, argv8), ParseArgException);
    const char *argv9[3] = {"sudoku.exe", "-r", "20~30"};
    EXPECT_THROW(parseArgs(3, argv9), ParseArgException);
    const char *argv10[5] = {"sudoku.exe", "-n", "1000", "-r", "20~60"};
    EXPECT_THROW(parseArgs(5, argv10), ParseArgException);
}
TEST(ExceptionTest, TestValidArgs)
{
    const char *argv1[3] = {"sudoku.exe", "-c", "20"};
    Command result1 = parseArgs(3, argv1);
    EXPECT_EQ(result1.gameType, GENERATE_SOLUTION_MAP);
    EXPECT_EQ(result1.gameNumber, 20);
    //make a new game.txt
    std::ofstream out("game.txt");
    out.close();
    const char *argv2[3] = {"sudoku.exe", "-s", "game.txt"};
    Command result2 = parseArgs(3, argv2);
    EXPECT_EQ(result2.gameType, SOLVE_SUDOKU);
    EXPECT_EQ(result2.filePath, "game.txt");
    const char *argv3[3] = {"sudoku.exe", "-n", "1000"};
    Command result3 = parseArgs(3, argv3);
    EXPECT_EQ(result3.gameType, GENERATE_SUDOKU);
    EXPECT_EQ(result3.gameNumber, 1000);
    const char *argv4[5] = {"sudoku.exe", "-n", "1000", "-m", "1"};
    Command result4 = parseArgs(5, argv4);
    EXPECT_EQ(result4.gameType, GENERATE_SUDOKU);
    EXPECT_EQ(result4.gameNumber, 1000);
    EXPECT_EQ(result4.gameDifficulty, EASY);
    const char *argv5[5] = {"sudoku.exe", "-n", "20", "-r", "20~55"};
    Command result5 = parseArgs(5, argv5);
    EXPECT_EQ(result5.gameType, GENERATE_SUDOKU);
    EXPECT_EQ(result5.gameNumber, 20);
    EXPECT_EQ(result5.holeRange.first,20);
    EXPECT_EQ(result5.holeRange.second,55);
    const char *argv6[4] = {"sudoku.exe", "-n", "20", "-u"};
    Command result6 = parseArgs(4, argv6);
    EXPECT_EQ(result6.gameType, GENERATE_SUDOKU);
    EXPECT_EQ(result6.gameNumber, 20);
    EXPECT_EQ(result6.isUnique, true);
}
TEST(SolutionMapTest, TestSolutionMap)
{
    std::vector<Board> map = mapGenerate(10);
    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(testLegalSolutionMap(map[i]));
    }
}

TEST(GenerateMapTest, TestMapWriteAndRead)
{
    std::vector<Board> map = mapGenerate(10);
    EXPECT_TRUE(writeBoards2File(map, SOLUTION_MAP_PATH));
    EXPECT_FALSE(writeBoards2File(map, "nonexistent.txt"));
    std::ifstream fp(SOLUTION_MAP_PATH);
    int size;
    fp >> size;
    EXPECT_EQ(size, 10);
    Board board;
    for (int i = 0; i < 10; i++)
    {
        board.readBoard(fp);
        EXPECT_TRUE(testLegalSolutionMap(board));
    }
}

TEST(GenerateMapTest, TestMapBatchRead)
{
    std::vector<Board> map = mapGenerate(10);
    EXPECT_TRUE(writeBoards2File(map, SOLUTION_MAP_PATH));
    std::vector<Board> v;
    v = readBoardsFromFile(SOLUTION_MAP_PATH);
    EXPECT_EQ(v.size(), 10);
    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(testLegalSolutionMap(v[i]));
    }
    EXPECT_EQ(readBoardsFromFile("nonexistent.txt").size(), 0);
}

TEST(GenerateGameTest, TestLevel)
{
    Command c1(GENERATE_SUDOKU, 10, EASY);
    c1.showCommand();
    EXPECT_TRUE(distributeTask(c1));
    std::vector<Board> v;
    v = readBoardsFromFile(GAME_MAP_PATH);
    EXPECT_EQ(v.size(), 10);
    for (int i = 0; i < 10; i++)
    {
        EXPECT_TRUE(testRightCountOfBlank(v[i], std::pair<int, int>(20, 32)));
    }
    // medium and hard
    Command c2(GENERATE_SUDOKU, 2, MEDIUM);
    c2.showCommand();
    EXPECT_TRUE(distributeTask(c2));
    v = readBoardsFromFile(GAME_MAP_PATH);
    EXPECT_EQ(v.size(), 2);
    for (int i = 0; i < 2; i++)
    {
        EXPECT_TRUE(testRightCountOfBlank(v[i], std::pair<int, int>(33, 45)));
    }
    Command c3(GENERATE_SUDOKU, 2, HARD);
    c3.showCommand();
    EXPECT_TRUE(distributeTask(c3));
    v = readBoardsFromFile(GAME_MAP_PATH);
    EXPECT_EQ(v.size(), 2);
    for (int i = 0; i < 2; i++)
    {
        EXPECT_TRUE(testRightCountOfBlank(v[i], std::pair<int, int>(46, 55)));
    }
}

TEST(SolverTest, TestSolve)
{
    std::vector<std::vector<Board>> v;
    std::vector games=generateGame(mapGenerate(1), 20, 32);

    v= solveSudoku(std::move(games));
//    for(const auto& i:v)
//    {
//        for(auto j:i)
//        {
//
//            EXPECT_TRUE(testLegalSolutionMap(j));
//        }
//    }

}

TEST(SolverTest, TestSolveAll){
    Command c1(GENERATE_SUDOKU, 1, EASY);
    c1.showCommand();
    EXPECT_TRUE(distributeTask(c1));
    // rename sudoku.txt to game.txt
    rename(GAME_MAP_PATH, "game.txt");
    Command c2(SOLVE_SUDOKU, 0, "sudoku.txt");
    c2.showCommand();
    EXPECT_TRUE(distributeTask(c2));
    std::vector<Board> v;
    v = readBoardsFromFile(SOLUTION_MAP_PATH);
    EXPECT_EQ(v.size(), 1);
    for (int i = 0; i < 1; i++)
    {
        EXPECT_TRUE(testLegalSolutionMap(v[i]));
    }
}
TEST(VectorTest, TestVector)
{
    std::vector<std::vector<int>> v;
    std::vector<int> v1;
    v1.push_back(1);
    std::vector<int> v2;
    v.push_back(v1);
    v.push_back(v2);
    EXPECT_EQ(v.size(), 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
