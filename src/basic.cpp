#pragma warning(disable:4996);
#include"basic.h"

static char buf[MAX];
bool mapGenerate(int n) {
    int count = n;
    Board* boards = new Board[count];
    int board_id = 0;
    buf[0] = '\0';
    int bit = 0;

    char basic_line[9] = { '5', '1', '2', '3', '4', '6', '7', '8', '9' };
    char pre_line[19] = { '5', ' ', '1', ' ', '2', ' ',
    '3', ' ', '4', ' ', '6', ' ', '7',
    ' ', '8', ' ', '9', '\n', '\0' };
    int shift[9] = { 0, 6, 12, 2, 8, 14, 4, 10, 16 };

    int pos1[6][3] = { 
        { 3, 4, 5 },
        { 3, 5, 4 },
        { 4, 5, 3 },
        { 4, 3, 5 },
        { 5, 4, 3 },
        { 5, 3, 4 }
    };
    int pos2[6][3] = { 
        { 6, 7, 8 }, 
        { 6, 8, 7 }, 
        { 7, 6, 8 },
        { 7, 8, 6 }, 
        { 8, 6, 7 }, 
        { 8, 7, 6 } 
    };

    char inter_result[10][19];
    int i, j, k;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 17; j++) {
            inter_result[i][j] = ' ';
        }
        inter_result[i][17] = '\n';
        inter_result[i][18] = '\0';
    }
    inter_result[9][0] = '\n';
    inter_result[9][1] = '\0';
    FILE* fp = fopen(SOLUTION_MAP_PATH, "w");

    do {
        for (int i = 0; i < 9; i++) {
            pre_line[2 * i] = basic_line[i];
        }
        memcpy(inter_result[0], pre_line, sizeof(pre_line));
        for (i = 1; i < 9; i++) {
            for (j = 0; j < 18; j += 2) {
                inter_result[i][j] = pre_line[(j + shift[i]) % 18];
            }
        }

        for (i = 0; i < 6; i++) {
            for (j = 0; j < 6; j++) {
                boards[board_id].initBoard();
                for (k = 0; k < 3; k++) {
                    strncpy(buf + bit, inter_result[k], 19);
                    for (int t = 0; t < 9; t++)
                    {
                        boards[board_id].pos[k][t] = (int)(buf + bit)[2 * t] - '0';
                    }
                    bit += 18;
                }
                for (k = 0; k < 3; k++) {
                    strncpy(buf + bit, inter_result[pos1[i][k]], 19);
                    for (int t = 0; t < 9; t++)
                    {
                        boards[board_id].pos[3 + k][t] = (int)(buf + bit)[2 * t] - '0';
                    }
                    bit += 18;
                }
                for (k = 0; k < 3; k++) {
                    strncpy(buf + bit, inter_result[pos2[j][k]], 19);
                    for (int t = 0; t < 9; t++)
                    {
                        boards[board_id].pos[6 + k][t] = (int)(buf + bit)[2 * t] - '0';
                    }
                    bit += 18;
                }
                strncpy(buf + bit, "\n", 1);
                bit++;
                if (n == 1) {
                    buf[163 * (count - 1) + 161] = '\0';
                    fputs(buf, fp);
                }
                //cout << "id:" << board_id << endl;
                //boards[board_id].printBoard();
                //boards[board_id].testBoard();
                board_id++;
                n--;
                if (!n) {
                    fclose(fp);
                    return true;
                }
            }
        }
    } while (next_permutation(basic_line + 1, basic_line + 9));
    return false;
}

bool generateQuesN(int n) {
    char inter_result[200];
    inter_qb[9][1] = '\0';
    inter_qb[9][0] = '\n';
    
    Board* ques_boards = new Board[n];
    int board_id = 0;

    FILE* fpMap;
    FILE* fpQuestion;
    
    fpQuestion = fopen(QUESTION_PATH, "w");
    fpMap = fopen(SOLUTION_MAP_PATH, "r");

    while (n--) {
        inter_result[0] = '\0';
        for (int i = 0; i < 9; i++) {
            fgets(inter_qb[i], 20, fpMap);
        }
        fgetc(fpMap);
        int und[9] = { 0, 6, 12, 54, 60, 66, 108, 114, 120 };
        int add[9] = { 0, 2, 4, 18, 20, 22, 36, 38, 40 };

        for (int k = 0; k < 9; k++) {
            int i, j,temp[2];
            temp[0] = rand() % 9;
            temp[1] = rand() % 9;
            while (temp[0] == temp[1]) {
                temp[1] = rand() % 9;
            }
            for (int u = 0; u < 2; u++) {
                int g;
                g = und[k] + add[temp[u]];
                i = g / 18;
                j = g % 18;
                inter_qb[i][j] = '0';
            }
        }

        int par;
        par = 2 + rand() % 19;
        while (par--) {
            int k = rand() % 81;
            int i = k / 9;
            int j = k % 9;
            j *= 2;
            if (inter_qb[i][j] != '0')
                inter_qb[i][j] = '0';
            else
                par++;
        }

        for (int i = 0; i < 10; i++) {
            strncat(inter_result, inter_qb[i], 20);
            //cout << inter_qb[i];
            if (i < 9) {
                for (int m = 0; m < 9; m++)
                {
                    ques_boards[board_id].pos[i][m] = inter_qb[i][2 * m] - '0';
                }
            }
        }
        if (!n) {
            inter_result[161] = '\0';
        }

        //cout << "id:" << board_id << endl;
        //ques_boards[board_id].printBoard();
        board_id++;

        fputs(inter_result, fpQuestion);
    }
    fclose(fpQuestion);
    fclose(fpMap);

    return true;
}

bool generateQuesM(int n, int level) {
    Board* ques_boards = new Board[n];
    int board_id = 0;
    char inter_result[200];
    inter_qb[9][0] = '\n';
    inter_qb[9][1] = '\0';

    FILE* fpQuestion;
    FILE* fpMap;
    fpMap = fopen(SOLUTION_MAP_PATH, "r");
    fpQuestion = fopen(QUESTION_PATH, "w");
    
    while (n--) {
        inter_result[0] = '\0';
        for (int i = 0; i < 9; i++) {
            fgets(inter_qb[i], 20, fpMap);
        }
        fgetc(fpMap);
        int und[9] = { 0, 6, 12, 54, 60, 66, 108, 114, 120 };
        int add[9] = { 0, 2, 4, 18, 20, 22, 36, 38, 40 };

        for (int k = 0; k < 9; k++) {
            int i, j,temp[2];
            temp[0] = rand() % 9;
            temp[1] = rand() % 9;
            while (temp[0] == temp[1]) {
                temp[1] = rand() % 9;
            }
            for (int t = 0; t < 2; t++) {
                int g;
                g = und[k] + add[temp[t]];
                j = g % 18;
                i = g / 18;
                inter_qb[i][j] = '0';
            }
        }

        int par = 0;  // 2-42
        // 2-20
        if (level == 1) {
            par = 2 + rand() % 19;
        }
        // 21-31 
        if (level == 2)
            par = 21 + rand() % 11;
        // 32-42 
        if (level == 3)
            par = 32 + rand() % 11;
        while (par--) {
            int k = rand() % 81;
            int i = k / 9;
            int j = k % 9;
            j *= 2;
            if (inter_qb[i][j] != '0')
                inter_qb[i][j] = '0';
            else
                par++;
        }

        for (int i = 0; i < 10; i++) {
            strncat(inter_result, inter_qb[i], 20);
            if (i < 9) {
                for (int m = 0; m < 9; m++)
                {
                    ques_boards[board_id].pos[i][m] = inter_qb[i][2 * m] - '0';
                }
            }
        }
        if (!n) {
            inter_result[161] = '\0';
        }

        //cout << "id:" << board_id << endl;
        //ques_boards[board_id].printBoard();
        board_id++;

        fputs(inter_result, fpQuestion);
    }
    fclose(fpMap);
    fclose(fpQuestion);

    return true;
}