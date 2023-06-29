#ifndef BASIC
#define BASIC


#include <algorithm>
#include<vector>
#include "board.h"
#include "color_print.h"
#include "solver.h"

#define SOLUTION_MAP_PATH  "sudoku.txt"
#define GAME_MAP_PATH  "sudoku.txt"
extern std::vector<Board> mapGenerate(int n);
extern bool writeBoards2File(const std::vector<Board> &boards,const std::string& path);
extern std::vector<Board> generateGame(std::vector<Board>&& boards,int minHole,int maxHole,bool isUnique=false);
extern std::vector<Board> readBoardsFromFile(const std::string& filePath);
extern std::vector<std::vector<Board>> solveSudoku(std::vector<Board> &&boards);
extern bool writeAnswers2File(std::vector<std::vector<Board>>&& solutions);
#endif  
