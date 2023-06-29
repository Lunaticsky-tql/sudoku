#ifndef BOARD
#define BOARD

#include<vector>
#include<fstream>
#include<cstring>
#include <random>

constexpr int BOARD_SIZE = 9;
constexpr int BOX_SIZE = 3;

// create random generator for c++11
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> dis0to8(0, BOARD_SIZE-1);
static std::uniform_int_distribution<> dis0to2(0, BOX_SIZE - 1);

inline int rd0to8() {
    return dis0to8(gen);
}

inline int rd0to2() {
    return dis0to2(gen);
}

class Board {
public:
    int pos[9][9]{};

    Board() {
        memset(pos, 0, sizeof(pos));
    }

    void printBoard(std::ofstream &file) const {
        for (auto &po: pos) {
            for (int j: po) {
                if (j == 0)
                    file << '$' << ' ';
                else
                    file << j << ' ';
            }
            file << '\n';
        }
        file << '\n';
    }
    void readBoard(std::ifstream &file) {
        for (auto &po: pos) {
            for (int &j: po) {
                char c;
                file >> c;
                if (c == '$')
                    j = 0;
                else
                    j = c - '0';
            }
        }
    }

    void swapRowsInBox(int boxRow) {
        int row1 = (boxRow * BOX_SIZE) + rd0to2();
        int row2 = (boxRow * BOX_SIZE) + rd0to2();
        while (row1 == row2) {
            row2 = (boxRow * BOX_SIZE) + rd0to2();
        }

        for (int i = 0; i < BOARD_SIZE; i++) {
            std::swap(pos[row1][i], pos[row2][i]);
        }
    }

    void swapColumnsInBox(int boxCol) {
        int col1 = (boxCol * BOX_SIZE) +rd0to2();
        int col2 = (boxCol * BOX_SIZE) + rd0to2();

        while (col1 == col2) {
            col2 = (boxCol * BOX_SIZE) + rd0to2();
        }

        for (int i = 0; i < BOARD_SIZE; i++) {
            std::swap(pos[i][col1], pos[i][col2]);
        }
    }

    void shuffleBoard() {
        for (int i = 0; i < rd0to8(); i++) {
            swapRowsInBox(rd0to2());
            swapColumnsInBox(rd0to2());
        }
    }
    int *operator[](int i) {
        return pos[i];
    }
};

#endif