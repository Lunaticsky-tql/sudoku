//
// Created by LENOVO on 2023/6/30.
//

#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H
#include "board.h"

class SudoSolver{
private:
    int row_state[9];
    int column_state[9];
    int block_state[3][3];
    std::vector<Board> results;
    std::vector<std::pair<int, int>> spaces;
public:
    std::vector<Board> solve(Board &board);
    void dfs(Board &board, int pos);
    void flip(int i, int j, int digit);
    void clearState();
};

#endif