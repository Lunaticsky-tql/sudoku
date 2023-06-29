#ifndef BASIC
#define BASIC

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <time.h>
#include "board.h"
using namespace std;

#define SOLUTION_MAP_PATH  "sudoku.txt"
#define QUESTION_PATH "question.txt"
#define MAX 200000000
static char inter_qb[10][20];

extern bool mapGenerate(int n);
extern bool generateQuesN(int n);
extern bool generateQuesM(int n, int level);
#endif  
