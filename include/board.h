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
static std::uniform_int_distribution<> dis1to9(1, BOARD_SIZE);
static std::uniform_int_distribution<> dis0to2(0, BOX_SIZE - 1);

inline int rd1to9() {
    return dis1to9(gen);
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
        for (int i = 0; i < rd1to9(); i++) {
            swapRowsInBox(rd0to2());
            swapColumnsInBox(rd0to2());
        }
    }
    int *operator[](int i) {
        return pos[i];
    }

//    void testBoard() {
//        int i, j, k, l, m;
//        for (i = 0; i < 9; i++) {
//            for (j = 1; j <= 9; j++) {
//                for (k = 0; k < 9; k++) {
//                    if (pos[i][k] == j)
//                        break;
//                }
//                if (k == 9) {
//                    cout << "Board Error:Raw Error\n";
//                    return;
//                }
//
//
//                for (l = 0; l < 9; l++) {
//                    if (pos[l][i] == j)
//                        break;
//                }
//                if (l == 9) {
//                    cout << "Board Error:Col Error\n";
//                    return;
//                }
//
//            }
//
//        }
//
//        for (i = 0; i < 9; i += 3) {
//            for (j = 0; j < 9; j += 3) {
//                for (k = 1; k <= 9; k++) {
//                    for (l = i; l < i + 3; l++) {
//                        for (m = j; m < j + 3; m++) {
//                            if (pos[l][m] == k)
//                                break;
//                        }
//                        if (pos[l][m] == k)
//                            break;
//                    }
//                    if (l == i + 3) {
//                        cout << "Board Error:3*3 Error\n";
//                        return;
//                    }
//
//                }
//            }
//        }
//
//        cout << "Test Success!" << endl;
//    }
};

#endif