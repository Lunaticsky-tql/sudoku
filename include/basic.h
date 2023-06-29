#ifndef BASIC
#define BASIC


#include <algorithm>
#include<vector>
#include "board.h"
#include "color_print.h"
using namespace std;

#define SOLUTION_MAP_PATH  "sudoku.txt"
#define QUESTION_PATH "question.txt"
#define MAX 200000000
static char inter_qb[10][20];

extern vector<Board> mapGenerate(int n);
extern bool writeBoards2File(const vector<Board> &boards,const std::string& path);
//extern bool generateQuesN(int n);
//extern bool generateQuesM(int n, int level);
extern vector<Board> generateGame(vector<Board>&& boards,int minHole,int maxHole,bool isUnique);
#endif  
