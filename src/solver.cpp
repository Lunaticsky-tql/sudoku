//
// Created by LENOVO on 2023/6/30.
//
#include <cstring>
#include "solver.h"
std::vector<Board> SudoSolver::solve(Board &board)
{
    clearState();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j]==0) {
                spaces.emplace_back(i, j);
            } else {
                flip(i, j, board[i][j]);
            }
        }
    }
    dfs(board, 0);
    return results;
}

void SudoSolver::flip(int i, int j, int digit)
{
    row_state[i] ^= (1 << digit);
    column_state[j] ^= (1 << digit);
    block_state[i / 3][j / 3] ^= (1 << digit);
}

void SudoSolver::clearState(){
    memset(row_state, 0, sizeof(row_state));
    memset(column_state, 0, sizeof(column_state));
    memset(block_state, 0, sizeof(block_state));
    spaces.clear();
    results.clear();
}

void SudoSolver::dfs(Board& board, int pos){
    if (pos == spaces.size())
    {
//        board.printBoard();
        results.emplace_back(board);
        return;
    }
    auto[i, j] = spaces[pos];
    int mask = ~(row_state[i] | column_state[j] | block_state[i / 3][j / 3]) & 0x1ff;
    for (; mask; mask &= (mask - 1)) {
        int digitMask = mask & (-mask);
        int digit = __builtin_ctz(digitMask);
        flip(i, j, digit);
        board[i][j] = digit;
        dfs(board, pos + 1);
        flip(i, j, digit);
    }
}





