#pragma warning(disable:4996);
#include"basic.h"

static char buf[MAX];
bool mapGenerate(int n) {
    int board_num = n;
    Board* boards = new Board[board_num];
    int board_id = 0;
    int cot = n;
    buf[0] = '\0';
    int bit = 0;
    char line[9] = { '5', '1', '2', '3', '4', '6', '7', '8', '9' };
    char line1[19] = { '5', ' ', '1', ' ', '2', ' ',
    '3', ' ', '4', ' ', '6', ' ', '7',
    ' ', '8', ' ', '9', '\n', '\0' };
    int shift[9] = { 0, 6, 12, 2, 8, 14, 4, 10, 16 };

    int pos1[6][3] = { { 3, 4, 5 },
    { 3, 5, 4 },
    { 4, 5, 3 },
    { 4, 3, 5 },
    { 5, 4, 3 },
    { 5, 3, 4 } };
    int pos2[6][3] = { { 6, 7, 8 }, { 6, 8, 7 }, { 7, 6, 8 },
    { 7, 8, 6 }, { 8, 6, 7 }, { 8, 7, 6 } };

    char final[10][19];
    int i, j, k;
    int flag = 0;
    char str[200];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 17; j++) {
            final[i][j] = ' ';
        }
        final[i][17] = '\n';
        final[i][18] = '\0';
    }
    final[9][0] = '\n';
    final[9][1] = '\0';
    FILE* fp = fopen(SOLUTION_MAP_PATH, "w");

    do {
        for (int i = 0; i < 9; i++) {
            line1[2 * i] = line[i];
        }
        memcpy(final[0], line1, sizeof(line1));
        for (i = 1; i < 9; i++) {
            for (j = 0; j < 18; j += 2) {
                final[i][j] = line1[(j + shift[i]) % 18];
            }
        }


        for (i = 0; i < 6; i++) {
            for (j = 0; j < 6; j++) {
                str[0] = '\0';
                flag++;
                boards[board_id].initBoard();
                for (k = 0; k < 3; k++) {
                    strncpy(buf + bit, final[k], 19);
                    bit += 18;
                    for (int t = 0; t < 9; t++)
                    {
                        boards[board_id].pos[k][t] = (int)final[k][2 * t] - '0';
                    }
                }
                for (k = 0; k < 3; k++) {
                    strncpy(buf + bit, final[pos1[i][k]], 19);
                    bit += 18;
                    for (int t = 0; t < 9; t++)
                    {
                        boards[board_id].pos[3 + k][t] = (int)final[pos1[i][k]][2 * t] - '0';
                    }
                }
                for (k = 0; k < 3; k++) {
                    strncpy(buf + bit, final[pos2[j][k]], 19);
                    bit += 18;
                    for (int t = 0; t < 9; t++)
                    {
                        boards[board_id].pos[6 + k][t] = (int)final[pos2[i][k]][2 * t] - '0';
                    }
                }
                strncpy(buf + bit, "\n", 1);
                bit++;
                if (n == 1) {
                    buf[163 * (cot - 1) + 161] = '\0';
                    fputs(buf, fp);
                }
                cout << "id:" << board_id << endl;
                boards[board_id].testBoard();
                board_id++;
                n--;
                if (!n) {
                    fclose(fp);
                    return true;
                }
            }
        }
    } while (next_permutation(line + 1, line + 9));
    return false;
}